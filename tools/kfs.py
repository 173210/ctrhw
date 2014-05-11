import sys;
import os
import struct


def HexToByte( hexStr ): 
    bytes = []

    hexStr = ''.join( hexStr.split(" ") )

    for i in range(0, len(hexStr), 2):
        bytes.append( chr( int (hexStr[i:i+2], 16 ) ) )

    return ''.join( bytes )


def ByteToHex( byteStr ):
    return ''.join( [ "%02X " % ord( x ) for x in byteStr ] ).strip()

files = {}
cfile = 0
offset = 0;

for i in xrange(1, len(sys.argv)):
	if (sys.argv[i][0:2] == "0x"):
		cfile["memloc"] = int(sys.argv[i],16)
		continue;
	if (sys.argv[i].isdigit()):
		cfile["memloc"] = int(sys.argv[i])
		continue;
	cfile = {}
	with open(sys.argv[i], "rb") as _file:
		cfile["name"] = os.path.basename(sys.argv[i])[:16].ljust(16, chr(0))
		cfile["content"] = _file.read()
		#_file.seek(0, os.SEEK_END)
		cfile["size"] = int(_file.tell()) 
		cfile["memloc"] = 0 
	#if (files[cfile["name"]]):
	#	print("Non unique filename")
	#	exit();	
	files[cfile["name"]] =cfile 	

file_header = ""
file_contents = ""
count = 0
for f in files.values():
	file_header += HexToByte(hex(f["memloc"])[2:].zfill(8))[::-1]
	file_header += HexToByte(hex(f["size"])[2:].zfill(8))[::-1]
	file_header += HexToByte(hex(len(file_contents))[2:].zfill(8))[::-1]
	file_header += f["name"]
	file_contents += f["content"]

for i in xrange(len(file_header), 0x150):
	file_header += chr(0)

outfile = file_header+file_contents

with open("kfs.bin", "wb") as _file:
	_file.write(outfile)

#while (1):

#	file_header = outfile[:0x150]
#	file_contents = outfile[0x150:]

#	location = file_header[i:i+4]
#	i += 4
#	size = file_header[i:i+4]
#	i +=4 
#	offset = file_header[i:i+4]
#	i += 4
#	name = file_header[i:i+16]

#	print name
#	print ByteToHex(offset)
#	print ByteToHex(location)
#	print ByteToHex(size)
#	i+=16
#	if (i > 0x150):
#		exit();
#ByteToHex(file_header)
#for f in file_headers:
#	print hex(f)[2:].zfill(8)
#	struct.unpack('<I', f)



#f1size = 0

#with open(sys.argv[1], "rb") as file1:
#	with open(sys.argv[2], "rb") as file2:
#		f1 = file1.read()
#		file1.seek(0, os.SEEK_END)
#		f1size = file1.tell()
#		f2 = file2.read()

#with open(sys.argv[3], "w+b") as file3:
#	file3.write(f1);
#	for x in range(f1size, 40960):
#		file3.write(chr(0))
	#file3.write(chr(0xDE));
	#file3.write(chr(0xAD));
	#file3.write(chr(0xBE));
	#file3.write(chr(0xEF));
	#file3.write(f2);