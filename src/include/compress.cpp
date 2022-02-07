#include "compress.h"

void compress_directory::walk_directory(const std::string& start_dir, const std::string& input_dir, zip_t *zipper) {

	// Iterate through directory input_dir
    bfs::directory_iterator end_itr;
    for (bfs::directory_iterator itr(input_dir); itr != end_itr; ++itr) {

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

void compress_directory::compress(const std::string& input_dir, const std::string& output_filename) {

	// Init zipper
	int errorp;
	zip_t *zipper = zip_open(output_filename.c_str(), ZIP_CREATE | ZIP_EXCL, &errorp);
	if (zipper == nullptr) {
		zip_error_t ziperror;
		zip_error_init_with_code(&ziperror, errorp);
		throw std::runtime_error("Failed to open output file " + output_filename + ": " + zip_error_strerror(&ziperror));
	}

	// Create the compressed file
	try {
		compress_directory::walk_directory(input_dir, input_dir, zipper);
	} catch(...) {
		zip_close(zipper);
		throw;
	}

	// Close the compressed file
	zip_close(zipper);
}

Json::Value compress_directory::gather_files(const std::string& input_dir, const std::string& output_dir) {

	// Create an array of file paths
	std::vector<std::string> paths = compress_directory::generate_file_array(input_dir);

	// Init Json
	Json::Value files;

	for (size_t d = 0; d < paths.size(); d++) {
		std::cout << "fiets";
		std::cout << paths[d] << std::endl;
	}

	return files;
}

std::vector<std::string> compress_directory::generate_file_array(const std::string& input_dir) {

	// Create a scalable array
	std::vector<std::string> paths {};

	// Iterate through directory input_dir
    bfs::directory_iterator end_itr;
    for (bfs::directory_iterator itr(input_dir); itr != end_itr; ++itr) {

		// Current iteration name.
		std::string cur_name = itr->path().filename().string();

		// If current iteration is file
		if (bfs::is_regular_file(itr->path())) {
			paths.push_back(itr->path().string()); // Append to path array
		}

		// If current iteration is directory
		else {

			// Recursively call function again with current directory
			compress_directory::generate_file_array(input_dir + "/" + cur_name); 
		}
	}

	return paths;
}