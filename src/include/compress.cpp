/*

 *  FMM Directory Compressor

 *  Copyright (C) 2022  Wibo Kuipers
 
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.

 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.

 *  You should have received a copy of the GNU General Public License
 *  along with this program.  
 *  If not, see https://github.com/w-kuipers/fmm-directory-compressor/blob/master/LICENSE.
 
 */

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

std::string decompress_archive::decompress(const char *file_string, const char *to_fetch) {
	// Open the FSA archive
    int err = 0;
    zip *z = zip_open(file_string, 0, &err);

    // Search for the structure.json file
    const char *name = to_fetch;
    struct zip_stat st;
    zip_stat_init(&st);
    zip_stat(z, name, 0, &st);

    // Allocate memory for JSON file
    char *contents = new char[st.size];

    // Read the compressed structure file
    zip_file *f = zip_fopen(z, name, 0);
    zip_fread(f, contents, st.size);
    zip_fclose(f);
    zip_close(z);
	std::string read_data = contents;

    // Delete allocated memory
    delete[] contents;

	return read_data;
	
}

void decompress_archive::decompress_bin(const char *file_string, const char *to_fetch, std::string location) {

	// Definitions
    int err;
    struct zip *za;
	struct zip_file *zf;
	char buf[100];
	struct zip_stat sb;
	int len;
	int fd;
	long long sum;
	
	
	// Open archive
	if ((za = zip_open(file_string, 0, &err)) == NULL) {
		zip_error_to_str(buf, sizeof(buf), err, errno);
        fprintf(stderr, "Can't open zip archive `%s': %s\n",
            file_string, buf);
       	exit(1);
	}

	if (zip_stat(za, to_fetch, 0, &sb) == 0) {

		// Get name of current iteration
		len = strlen(sb.name);

		zf = zip_fopen(za, to_fetch, 0);
		if (!zf) {
			fprintf(stderr, "boese, boese\n");
			exit(100);
		}

		sum = 0;

		// Open a file in specified location
		#ifdef _WIN32
		fd = open((location + "/" + sb.name).c_str(), O_RDWR | O_TRUNC | O_CREAT | O_BINARY, 0644); // Windows needs O_BINARY
		#endif
		#ifdef unix
		fd = open((location + "/" + sb.name).c_str(), O_RDWR | O_TRUNC | O_CREAT, 0644);
		#endif
		
		if (fd < 0) {
			fprintf(stderr, "boese, boese\n");
			exit(101);
		}
		while (sum != sb.size) {
			len = zip_fread(zf, buf, 100);
			if (len < 0) {
				fprintf(stderr, "boese, boese\n");
				exit(102);
			}
			write(fd, buf, len);
			sum += len;
		}
		close(fd);
		zip_fclose(zf);

	}
	else {
		printf("File[%s] Line[%d]\n", __FILE__, __LINE__);
	}

	// for (int i = 0; i < zip_get_num_entries(za, 0); i++) {
		
	// }

	// Close archive
	if (zip_close(za) == -1) {
        fprintf(stderr, "Can't close zip archive `%s'\n", file_string);
        exit(1);
    }

	return;	
}