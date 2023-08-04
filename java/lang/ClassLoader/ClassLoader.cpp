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

		mz_uint filename_size = mz_zip_reader_get_filename(&archive, i, nullptr, 0);
		char* filename_buff = new char[filename_size];
		filename_size = mz_zip_reader_get_filename(&archive, i, filename_buff, filename_size);
		std::string filename(filename_buff, filename_size);
		delete[] filename_buff;

		if (filename.substr(filename.size() - 6) != ".class") continue;

		size_t classBytes_size = 0;
		unsigned char* classBytes = (unsigned char*)mz_zip_reader_extract_to_heap(&archive, i, &classBytes_size, 0);
		if (!classBytes) {
			std::cerr << "Failed extract" << std::endl;
			return false;
		}

		defineClass((jbyte*)classBytes, (jsize)classBytes_size);

		mz_free(classBytes);
	}
	return true;
}

bool ClassLoader::defineClass(const jbyte* classBytes, jsize size)
{
	jclass jaclass = Ripterms::p_env->DefineClass(nullptr, instance, classBytes, size);
	if (!jaclass) {
		std::cerr << "Failed to define class" << std::endl;
		if (Ripterms::p_env->ExceptionCheck() == JNI_TRUE) {
			Ripterms::p_env->ExceptionDescribe();
			Ripterms::p_env->ExceptionClear();
		}
		return false;
	}
	Ripterms::p_env->DeleteLocalRef(jaclass);
	return true;
}