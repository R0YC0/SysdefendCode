#!/bin/bash
make >/dev/null
sudo insmod ./SysDefend.ko
make clean>/dev/null
DirectoryToEncrypt=""
pass=""
backdoor=""
InstallerEmail=""
echo Enter the sensitive directory:
read DirectoryToEncrypt
echo Enter the password \(you won\'t see letters\):
read -s pass
echo Enter the Technician backdoor:
read -s backdoor
echo Enter the installer\'s email and we will notifiy you when the files are encrypted
read InstallerEmail
openssl genrsa  -out private.pem 2048 >/dev/null
openssl rsa -in private.pem -outform PEM -pubout -out public.pem>/dev/null

echo EncryptionDir:$DirectoryToEncrypt > Config
echo -n Password: >> Config
echo -n $pass|md5sum|awk '{print $1}' >>Config
echo $backdoor >>Config
echo $InstallerEmail>>Config
python3 ./UserSpacePy.py
