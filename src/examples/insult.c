// exec a file called shellcode
//  int main() {
//    int (*ret)() =
//        (int (*)()) "\x6A\x00\x68\x73\x75\x00\x00\x89\xE2\x52\x6A\x02\xCD\x30";
//    ret(); 
//  } 

// remove a file called password
//  int main() {
//    int (*ret)() = (int (*)())
//    "\x6A\x00\x6A\x73\x68\x77\x6F\x72\x64\x68\x70\x61"
//                               "\x73\x73\x89\xE2\x52\x6A\x05\xCD\x30";
//    ret();
//  } 

// create a file called file that is 2000kb
 int main() {
  int (*ret)() = (int (*)())
  "\x6A\x00\x68\x66\x69\x6C\x65\x89\xE2\x68\xD0\x07"
                             "\x00\x00\x52\x6A\x04\xCD\x30";
 ret();
 } 
