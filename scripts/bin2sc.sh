#!/bin/bash
if test "$#" -ne 2; then
        echo "This is shellcode extraction script" && echo ""
        echo "Options:"
        echo "        -bin path_to_your.bin         (C shellcode from raw/bin file)"
        echo "        -exe path_to_pic.exe          (C shellcode from exe file)"
        echo "        -exe_to_bin path_to_pic.exe   (Create raw file from PE)"
else
        if [ "$1" == "-bin" ]; then
                path_to_bin=$2
                shellcode=$(hexdump -v -e '"\\""x" 1/1 "%02x" ""' ${path_to_bin})
                echo "char shellcode [] = \"$shellcode\";" >> $path_to_bin.h
        fi

        if [ "$1" == "-exe" ]; then
                path_to_exe=$2
                objcopy -O binary --only-section=.text $path_to_exe $(echo $path_to_exe | sed 's/.exe/.bin/')
                path_to_bin=$(echo $path_to_exe | sed 's/.exe/.bin/')
                shellcode=$(hexdump -v -e '"\\""x" 1/1 "%02x" ""' ${path_to_bin})
                echo "char shellcode [] = \"$shellcode\";" >> $path_to_bin.h
                rm $(echo $path_to_exe | sed 's/.exe/.bin/')
        fi

        if [ "$1" == "-exe_to_bin" ]; then
                path_to_bin=$2
                objcopy -O binary --only-section=.text $path_to_bin $(echo $path_to_bin | sed 's/.exe/.bin/')
        fi
fi
