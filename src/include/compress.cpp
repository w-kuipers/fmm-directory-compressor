#include "compress.h"

static void walk_directory(const std::string& start_dir, const std::string& input_dir, zip_t *zipper) {

	// Iterate through directory input_dir
    bfs::directory_iterator end_itr;
    for (bfs::directory_iterator itr( input_dir );itr != end_itr; ++itr) {

		// Full path name
		std::string fullname = input_dir + "/" + itr->path().filename().string();

		// If current iteration is directory
        if (!bfs::is_regular_file(itr->path())) {
			if (zip_dir_add(zipper, fullname.substr(start_dir.length() + 1).c_str(), ZIP_FL_ENC_UTF_8) < 0) {
				throw std::runtime_error("Failed to add directory to zip: " + std::string(zip_strerror(zipper)));
			}
			walk_directory(start_dir, fullname, zipper);
		}

		// If current iteration is file
		else {
			zip_source_t *source = zip_source_file(zipper, fullname.c_str(), 0, 0);
			if (source == nullptr) {
				throw std::runtime_error("Failed to add file to zip: " + std::string(zip_strerror(zipper)));
			}
			if (zip_file_add(zipper, fullname.substr(start_dir.length() + 1).c_str(), source, ZIP_FL_ENC_UTF_8) < 0) {
				zip_source_free(source);
				throw std::runtime_error("Failed to add file to zip: " + std::string(zip_strerror(zipper)));
			}
		}
	}
}

static void zip_directory(const std::string& inputdir, const std::string& output_filename) {
	int errorp;
	zip_t *zipper = zip_open(output_filename.c_str(), ZIP_CREATE | ZIP_EXCL, &errorp);
	if (zipper == nullptr) {
		zip_error_t ziperror;
		zip_error_init_with_code(&ziperror, errorp);
		throw std::runtime_error("Failed to open output file " + output_filename + ": " + zip_error_strerror(&ziperror));
	}

	try {
		walk_directory(inputdir, inputdir, zipper);
	} catch(...) {
		zip_close(zipper);
		throw;
	}

	zip_close(zipper);
}