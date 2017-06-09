# CBlowfish
## how to use the blowfish tool

    qipingli@qipingli:~/project/CBlowfish$ ./blowfish -e "helloworld" -k "wapwap12" -i "01234567"
    inputText:[helloworld]
    blowfishEncrypt/base64Encode:[NXp/7N7P6ozYgQ+aKW/OmHIReY3MGbv8]
    qipingli@qipingli:~/project/CBlowfish$ ./blowfish -d "NXp/7N7P6ozYgQ+aKW/OmHIReY3MGbv8" -k "wapwap12" -i "01234567"
    inputText:[NXp/7N7P6ozYgQ+aKW/OmHIReY3MGbv8]
    base64Decode/blowfishDecrypt:[helloworld]
