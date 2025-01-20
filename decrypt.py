# START
# NS BFW, JAJSYX TK NRUTWYFSHJ FWJ YMJ WJXZQY TK YWNANFQ HFZXJX
# END
# START
# N BTZQI WFYMJW GJ KNWXY NS F QNYYQJ NGJWNFS ANQQFLJ YMFS XJHTSI NS WTRJ
# END
# START
# IFSLJW PSTBX KZQQ BJQQ YMFY HFJXFW NX RTWJ IFSLJWTZX YMFS MJ
# END
# ENDOFINPUT


def decrypt(text):
    decrypted = ""
    for char in text:
        if char.isalpha():
            ascii_code = ord(char) - 5
            if ascii_code < 65:
                ascii_code += 26
            decrypted += chr(ascii_code)
        else:
            decrypted += char
    return decrypted

text = input()
result = []
while text != "ENDOFINPUT":
    if text != "START" and text != "END":
        result.append(decrypt(text))
    text = input()

for i in result:
    print(i)
