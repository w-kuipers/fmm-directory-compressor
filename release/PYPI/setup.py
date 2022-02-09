import setuptools


from sys import platform
if platform == "linux" or platform == "linux2":
    src_location = "src/unix"
elif platform == "win32":
    src_location = "src/win32"


with open("README.md", "r", encoding="utf-8") as fh:
    long_description = fh.read()



setuptools.setup(
    name="fmmpy-directory-compressor",
    version="0.1.0",
    author="Wibo Kuipers",
    author_email="w.kuipers@filmage.nl",
    description="Compress a directory into a single .FPS file.",
    long_description=long_description,
    long_description_content_type="text/markdown",
    url="https://github.com/w-kuipers/fmm-directory-compressor",
    project_urls={
        "Bug Tracker": "https://github.com/w-kuipers/fmm-directory-compressor/issues",
    },
    classifiers=[
        "Programming Language :: Python :: 3",
        "License :: OSI Approved :: GNU General Public License v3 (GPLv3)",
        "Operating System :: POSIX :: Linux",
        "Operating System :: Microsoft :: Windows",
    ],
    package_dir={"": src_location},
    packages=setuptools.find_packages(where=src_location),
    python_requires=">=3.8",
)