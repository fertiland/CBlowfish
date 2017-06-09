all:
	gcc -o blowfish_std blowfish_std.c base64.c -lssl -lcrypto -ldl
	gcc -o blowfish blowfish.c base64.c -lssl -lcrypto -ldl
