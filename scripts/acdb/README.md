# Stock ACDB query tool

Builds against AudioReach graphservices' own ACDB parser and asks the phone's
calibration database for graphs the way Android's audio stack does.

    git clone --depth 1 https://github.com/AudioReach/audioreach-graphservices gs
    O=gs/ar_osal/src/linux
    gcc -w -fpermissive -D__unused= \
      -Igs/acdb/api -Igs/acdb/inc -Igs/ar_osal/api -Igs/ar_util/api -Igs/public_headers \
      -o acdbq acdbq.c stubs.c gs/acdb/src/*.c \
      $O/ar_osal_file_io.c $O/ar_osal_heap.c $O/ar_osal_mem_op.c $O/ar_osal_string.c $O/ar_osal_mutex.c -lpthread
    ./acdbq /abs/path/Mise_elus_acdb_cal.acdb                       # list GKVs
    ./acdbq /abs/path/Mise_elus_acdb_cal.acdb " a1000000=a1000003 a2000000=a2000001" > spk.txt
    python3 decode.py spk.txt

The ACDB path must be absolute. Speaker = device key 0xA2000000 value 0xA2000001.
