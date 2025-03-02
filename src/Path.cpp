
/* Copyright © 2017-2025 Jordan Irwin (AntumDeluge) <antumdeluge@gmail.com>
 *
 * This file is part of the MMLE project & is distributed under the
 * terms of the MIT/X11 license. See: LICENSE.txt
 */

#define fs_supported __cplusplus >= 201703L

#include <algorithm> // transform
#include <sstream>

#if fs_supported
#include <filesystem>
#endif

using namespace std;

#include "MMLE/Path.hpp"
#include "MMLE/String.hpp"


/** Removes relative cwd prefix from path.
 *
 *  @param path
 *      String path to be trimmed.
 *  @return
 *      Trimmed path.
 */
string trimLeadingCWD(const string path) {
#ifdef __WIN32__
	if (path.substr(0, 3) == ".\\\\") {
		return path.substr(3);
	} else if (path.substr(0, 2) == ".\\") {
		return path.substr(2);
	}
#else
	if (path.substr(0, 2) == "./") {
		return path.substr(2);
	}
#endif

	return path;
}

string MMLE::Path::norm(const string path) {
	if (MMLE::String::checkEmptyString(path)) {
		// replace empty path with relative cwd
		return MMLE::Path::norm("./");
	}

	string new_path = path;

#ifdef __WIN32__
	const string sep = "\\";
	new_path = MMLE::String::replaceAll(MMLE::String::replaceAll(new_path, "/", sep), "\\\\", sep);

	// MSYS2/MinGW paths
	// FIXME: I don't remember why this is used
	string first_chars = new_path.substr(0, 3);
	transform(first_chars.begin(), first_chars.end(), first_chars.begin(), ::tolower);

	// TODO: support all drive letters
	if (first_chars == "\\c\\") {
		new_path.replace(0, 2, "C:");
	}
#else
	const string sep = "/";
	new_path = MMLE::String::replaceAll(MMLE::String::replaceAll(new_path, "\\", sep), "//", sep);
#endif

	// remove redundant node separators
	new_path = MMLE::String::replaceAll(new_path, sep + "." + sep, sep);

	// remove trailing node separator
	if (new_path.substr(new_path.length() - 1, 1) == sep) {
		new_path = new_path.substr(0, new_path.length() - 1);
	}

	return trimLeadingCWD(new_path);
}


string MMLE::Path::join(const string a, const string b) {
	return MMLE::Path::norm(a + "/" + b);
}


string MMLE::Path::basename(string path) {
#if fs_supported
	return filesystem::path(path).filename().string();
#else
	string _basename = path;
	int s_idx = path.find_last_of('/', '\\');
	if (s_idx >= 0) {
		_basename.erase(0, s_idx + 1);
	}
	return _basename;
#endif /* fs_supported */
}


string MMLE::Path::dirname(string path) {
#if fs_supported
	string _dirname = filesystem::path(path).parent_path().string();
#else
	string _dirname = path;
	int s_idx = path.find_last_of('/', '\\');
	if (s_idx < 0) {
		// working directory
		return ".";
	} else if (s_idx == 0) {
		// root of the filesystem
		return MMLE::Path::norm("/");
	} else {
		_dirname.erase(s_idx, path.length() - s_idx);
	}
#endif /* fs_supported */
	return MMLE::Path::norm(_dirname);
}
