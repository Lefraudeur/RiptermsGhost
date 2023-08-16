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
	jclass jaclass = Ripterms::p_env->DefineClass(nullptr, instance, classBytes, size);
	if (!jaclass)
	{
		std::cerr << "Failed to define class" << std::endl;
		if (Ripterms::p_env->ExceptionCheck() == JNI_TRUE)
		{
			Ripterms::p_env->ExceptionDescribe();
			Ripterms::p_env->ExceptionClear();
		}
		return false;
	}
	Ripterms::p_env->DeleteLocalRef(jaclass);
	return true;
}

ClassLoader ClassLoader::newObject()
{
	//for some reason impossible to create a ClassLoader object
	//So I was lazy and used a URLClassLoader instead with a random url
	jclass urlClass = Ripterms::p_env->FindClass("java/net/URL");
	jmethodID urlContructor = Ripterms::p_env->GetMethodID(urlClass, "<init>", "(Ljava/lang/String;)V");
	jstring str = Ripterms::p_env->NewStringUTF("file://ftp.yoyodyne.com/pub/files/foobar.txt");
	jobject url = Ripterms::p_env->NewObject(urlClass, urlContructor, str);
	jobjectArray urls = Ripterms::p_env->NewObjectArray(1, urlClass, url);
	jclass URLClassLoaderClass = Ripterms::p_env->FindClass("java/net/URLClassLoader");
	jmethodID URLClassLoaderContructor = Ripterms::p_env->GetMethodID(URLClassLoaderClass, "<init>", "([Ljava/net/URL;)V");
	jobject URLClassLoader = Ripterms::p_env->NewObject(URLClassLoaderClass, URLClassLoaderContructor, urls);

	Ripterms::p_env->DeleteLocalRef(urlClass);
	Ripterms::p_env->DeleteLocalRef(url);
	Ripterms::p_env->DeleteLocalRef(str);
	Ripterms::p_env->DeleteLocalRef(urls);
	Ripterms::p_env->DeleteLocalRef(URLClassLoaderClass);

	return ClassLoader(URLClassLoader);
}
