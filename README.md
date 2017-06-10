# CBlowfish

## How to use the blowfish tool

### special blowfish 

    qipingli@qipingli:~/project/CBlowfish$ ./blowfish -e "helloworld" -k "defautpasswd" -i "01234567"
    inputText:[helloworld]
    blowfishEncrypt/base64Encode:[5rVGSU2Gx6x8AyM7o0zTGT1giRIxqHP3]
    qipingli@qipingli:~/project/CBlowfish$ ./blowfish -d "5rVGSU2Gx6x8AyM7o0zTGT1giRIxqHP3" -k "defautpasswd" -i "01234567"
    inputText:[5rVGSU2Gx6x8AyM7o0zTGT1giRIxqHP3]
    base64Decode/blowfishDecrypt:[helloworld]

### standard blowfish 

    qipingli@qipingli:~/project/CBlowfish$ ./blowfish_std -e "helloworld" -k "defautpasswd" -i "01234567"
    inputText:[helloworld]
    blowfishEncrypt/base64Encode:[5rVGSU2Gx6yOdRqKIaBBKg==]
    qipingli@qipingli:~/project/CBlowfish$ ./blowfish_std -d "5rVGSU2Gx6yOdRqKIaBBKg==" -k "defautpasswd" -i "01234567"
    inputText:[5rVGSU2Gx6yOdRqKIaBBKg==]
    base64Decode/blowfishDecrypt:[helloworld]
