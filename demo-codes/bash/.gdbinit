python
import sys
sys.path.insert(0, '/home/opt/gcc-4.8.2.bpkg-r2/gcc-4.8.2.bpkg-r2/share/gcc-4.8.2/python')
from libstdcxx.v6.printers import register_libstdcxx_printers
register_libstdcxx_printers (None)
end

source /home/work/gdb/boost-gdb-printers/boost-gdb-printers.py 

set listsize 40
set print elements 0 

add-auto-load-safe-path /home/opt/gcc-4.8.2.bpkg-r2/gcc-4.8.2.bpkg-r2/lib64/libstdc++.so.6.0.19-gdb.py
add-auto-load-safe-path /home/opt/gcc-4.8.2.bpkg-r2/gcc-4.8.2.bpkg-r2/lib64/libthread_db-1.0.so
set auto-load safe-path /

