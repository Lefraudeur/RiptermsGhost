#include "ClassLoader.h"
#include <miniz/miniz.h>
#include <filesystem>

bool ClassLoader::loadJar(const unsigned char* jarBytes, size_t size)
{
	mz_zip_archive archive{};
	if (!mz_zip_reader_init_mem(&archive, jarBytes, size, 0)) {
		std::cerr << "Incorrect jar format" << std::endl;
		return false;
	}
	mz_uint file_number = mz_zip_reader_get_num_files(&archive);
	for (mz_uint i = 0; i < file_number; i++) {

		if (!mz_zip_reader_is_file_supported(&archive, i) || mz_zip_reader_is_file_a_directory(&archive,  i)) continue;

		char str[256] = { 0 };
		mz_zip_reader_get_filename(&archive, i, str, 256);
		std::string filename(str);

		if (filename.substr(filename.size() - 6) == ".class") {
			std::cout << filename << std::endl;

			size_t classBytes_size = 0;
			unsigned char* classBytes = (unsigned char*)mz_zip_reader_extract_to_heap(&archive, i, &classBytes_size, 0);
			if (!classBytes) {
				std::cerr << "Failed extract" << std::endl;
				mz_zip_reader_end(&archive);
				return false;
			}

			defineClass((jbyte*)classBytes, (jsize)classBytes_size);

			mz_free(classBytes);
		}
	}
	mz_zip_reader_end(&archive);
	return true;
}

bool ClassLoader::defineClass(const jbyte* classBytes, jsize size)
{
	jclass jaclass = env->DefineClass(nullptr, instance, classBytes, size);
	if (!jaclass)
	{
		std::cerr << "Failed to define class" << std::endl;
		if (env->ExceptionCheck() == JNI_TRUE)
		{
			env->ExceptionDescribe();
			env->ExceptionClear();
		}
		return false;
	}
	env->DeleteLocalRef(jaclass);
	return true;
}

jclass ClassLoader::findClass(const std::string& class_path) const
{
	static jmethodID findClass_mid = nullptr;
	if (!findClass_mid)
	{
		jclass classLoaderClass = env->FindClass("java/lang/ClassLoader");
		findClass_mid = env->GetMethodID(classLoaderClass, "findClass", "(Ljava/lang/String;)Ljava/lang/Class;");
		env->DeleteLocalRef(classLoaderClass);
	}
	jstring str = env->NewStringUTF(class_path.c_str());
	jclass found_class = (jclass)env->CallObjectMethod(instance, findClass_mid, str);
	env->DeleteLocalRef(str);
	return found_class;

	/* this somehow doesn't find not loaded classes
	if (!instance) return jclass();
	jclass found_class = nullptr;
	jint class_count = 0;
	jclass* class_list = nullptr;
	Ripterms::p_tienv->GetClassLoaderClasses(instance, &class_count, &class_list);
	for (jint i = 0; i < class_count; ++i)
	{
		char* sig_buff = nullptr;
		Ripterms::p_tienv->GetClassSignature(class_list[i], &sig_buff, nullptr);
		std::string signature = sig_buff;
		Ripterms::p_tienv->Deallocate((unsigned char*)sig_buff);
		signature = signature.substr(1, signature.size() - 2);
		if (signature == class_path)
		{
			found_class = (jclass)env->NewLocalRef(class_list[i]);
			break;
		}
	}
	for (jint i = 0; i < class_count; ++i)
	{
		env->DeleteLocalRef(class_list[i]);
	}
	Ripterms::p_tienv->Deallocate((unsigned char*)class_list);
	return found_class;
	*/
}

ClassLoader ClassLoader::newObject(JNIEnv* env)
{
	//for some reason impossible to create a ClassLoader object
	//So I was lazy and used a URLClassLoader instead with a random url
	jclass urlClass = env->FindClass("java/net/URL");
	jmethodID urlContructor = env->GetMethodID(urlClass, "<init>", "(Ljava/lang/String;)V");
	jstring str = env->NewStringUTF("file://ftp.yoyodyne.com/pub/files/foobar.txt");
	jobject url = env->NewObject(urlClass, urlContructor, str);
	jobjectArray urls = env->NewObjectArray(1, urlClass, url);
	jclass URLClassLoaderClass = env->FindClass("java/net/URLClassLoader");
	jmethodID URLClassLoaderContructor = env->GetMethodID(URLClassLoaderClass, "<init>", "([Ljava/net/URL;)V");
	jobject URLClassLoader = env->NewObject(URLClassLoaderClass, URLClassLoaderContructor, urls);

	env->DeleteLocalRef(urlClass);
	env->DeleteLocalRef(url);
	env->DeleteLocalRef(str);
	env->DeleteLocalRef(urls);
	env->DeleteLocalRef(URLClassLoaderClass);

	return ClassLoader(URLClassLoader, env);
}

ClassLoader ClassLoader::getMinecraftClassLoader(JNIEnv* env)
{
	jobject classLoader = nullptr;
	jint thread_count = 0;
	jthread* thread_list = nullptr;
	Ripterms::p_tienv->GetAllThreads(&thread_count, &thread_list);
	for (jint i = 0; i < thread_count; ++i)
	{
		jvmtiThreadInfo thread_info{};
		Ripterms::p_tienv->GetThreadInfo(thread_list[i], &thread_info);
		if (thread_info.name && !std::strcmp(thread_info.name, "Client thread"))
		{
			classLoader = thread_info.context_class_loader;
			Ripterms::p_tienv->Deallocate((unsigned char*)thread_info.name);
			env->DeleteLocalRef(thread_info.thread_group);
			break;
		}
		Ripterms::p_tienv->Deallocate((unsigned char*)thread_info.name);
		env->DeleteLocalRef(thread_info.context_class_loader);
		env->DeleteLocalRef(thread_info.thread_group);
	}
	for (jint i = 0; i < thread_count; ++i)
	{
		env->DeleteLocalRef(thread_list[i]);
	}
	Ripterms::p_tienv->Deallocate((unsigned char*)thread_list);

	return ClassLoader(classLoader, env);
}
