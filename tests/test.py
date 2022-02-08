import sys

sys.path.insert(0, '../build/Debug')

from fmmpy_directory_compressor import compress_directory, decompress_directory

# compress_directory('C:/Users/wkuip/Desktop/code/FMM_dirstructure_generator/tests/to_use', 'Pythontest', './pythonTests/', True)

decompress_directory('pythonMappie', 'pythonTests/Pythontest.fps', './pythonTests/')