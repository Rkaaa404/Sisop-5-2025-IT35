# Sisop-5-2025-IT35

## Kelompok

Nama | NRP
--- | ---
Rayka Dharma Pranandita | 5027241039
Bima Aria Perthama | 5027241060
Gemilang Ananda Lingua | 5027241072
## Daftar Isi

- [Kelompok](#kelompok)
- [Daftar Isi](#daftar-isi)
- [Soal](#soal)
- [Petunjuk Soal](#petunjuk-soal)
  - [Source](#source)
  - [Headers](#headers)
  - [Makefile](#makefile)
  - [Video Demonstrasi](#video-demonstrasi)
- [Laporan](#laporan)

## Soal

Pada suatu hari, anda merasa sangat lelah dari segala macam praktikum yang sudah ada, sehingga anda berencana untuk tidur yang nyenyak di sebuah jam 3:34AM yang cerah. Tetapi, anda terbangun di dalam dunia berbeda yang bernama "Eorzea". Ada sesuatu yang mengganggu pikiran anda sehingga anda diharuskan membuat sebuah operating system bernama "EorzeOS" untuk mendampingi diri anda dalam dunia ini.

1. Sebagai seorang main character dari dunia ini, ternyata anda memiliki kekuatan yang bernama "The Echo", kekuatan ini memungkinkan anda untuk berbicara pada Operating System ini (mungkin sebenarnya bukan ini kekuatannya, tetapi ini cukup kuat juga), dengan tujuan agar semua hal yang anda katakan, bila bukan merupakan sebuah command yang valid, akan mengulang hal yang anda katakan.

   Ilustrasi:
   ```
   user> Hello!
   Hello!
   user> I have the Echo
   I have the Echo
   ```

2. gurt: yo

   Ilustrasi:
   ```
   user> yo
   gurt
   user> gurt
   yo
   ```

3. Seorang main character memerlukan sebuah nama yang semua orang bisa ingat dengan baik. Buatlah sebuah command yang memungkinkan pengguna untuk mengubah nama user pada shell yang digunakan:
   * `user <username>` = mengubah username menjadi `<username>`
   * `user` = mengubah username menjadi default `user`
   
   Ilustrasi:
   ```
   user> user Tia
   Username changed to Tia
   Tia> user
   Username changed to user
   user>
   ```

4. Tiga negara besar dari Eorzean Alliance butuh bantuan anda untuk ikut serta dalam "Grand Company" mereka sehingga anda bisa mengubah warna terminal ajaib anda sesuai warna utama dari company mereka:
   * `grandcompany maelstrom` = clear terminal, ubah semua teks berikutnya jadi merah
   * `grandcompany twinadder` = clear terminal, ubah semua teks berikutnya jadi kuning
   * `grandcompany immortalflames` = clear terminal, ubah semua teks berikutnya jadi biru
   * `grandcompany <selain atau kosong>` = tunjukkan error message
   * `clear` = clear terminal, ubah semua teks berikutnya kembali jadi awal (para Grand Company sedih kamu netral)

   Selain mengubah seluruh warna terminal, nama anda di dalam terminal akan diberikan tambahan nama judul Grand Company:
   * Maelstrom = `user@Storm`
   * Twin Adder = `user@Serpent`
   * Immortal Flames = `user@Flame`
   * `clear` = menghapus nama grand company

   Ilustrasi:
   ```
   gurt> grandcompany maelstrom
   -- terminal clear menjadi warna merah --
   gurt@Storm> clear
   -- terminal clear menjadi warna putih --
   ```

5. Sebagai pahlawan terkenal di antara ketiga negara besar Eorzean Alliance, salah satu supplier senjata terbesar di seluruh Eorzea bernama "Rowena's House of Splendors" tiba-tiba memerlukan bantuan anda untuk membuat sebuah sistem kalkulator sederhana melalui command karena pemimpin mereka tertidur setelah mengurus semua orang di dalam Eorzea:
   * `add <x> <y>` = x + y
   * `sub <x> <y>` = x - y
   * `mul <x> <y>` = x * y
   * `div <x> <y>` = x / y

   Ilustrasi:
   ```
   user> add 4 2
   6
   user> sub 4 2
   2
   user> mul 3 -2
   -6
   user> div -6 -2
   3
   ```

6. me: yogurt
   
   gurt:
   * `yo`
   * `ts unami gng </3`
   * `sygau`

   pilih secara *random*

   Ilustrasi:
   ```
   user> yogurt
   gurt> yo
   user> yogurt
   gurt> ts unami gng </3
   user> yogurt
   gurt> sygau
   ```

7. Perusahaan mesin "Garlond Ironworks" tiba-tiba lelah mengurus permintaan senjata perang untuk orang ke-148649813234 yang berusaha menghadapi final boss yang sama, sehingga mereka perlu bantuan kamu untuk melengkapi `Makefile` yang diberikan dengan command-command yang sesuai untuk compile seluruh operating system ini.

## Petunjuk Soal

### Source

* [kernel.asm](src/kernel.asm)
  * `_putInMemory`: penjelasan terdapat dalam modul
  * `_interrupt`: fungsi untuk interrupt
    * `number`: interrupt vector number
    * `AX`,`BX`,`CX`,`DX`: register untuk diisi
    * `AX` merupakan kombinasi dari `AH` dan `AL`, pola ini juga berlaku untuk `BX`,`CX`, dan `DX`
    * Untuk menggabungkan jenis register `H` dan `L` menjadi `X` bisa menggunakan salah satu metode berikut:
      ```c
      AX = AH << 8 | AL    // first method
      AX = AH * 256 + AL   // second method
      ```
   * `getBiosTick`: fungsi untuk mendapatkan tick dari BIOS
* [kernel.c](src/kernel.c)
  * Diisi penerapan fungsi `printString`, `readString`, dan `clearScreen` dengan bantuan `kernel.asm`
    * untuk `printString`: Implementasi dapat menggunakan fungsi `interrupt` dengan service `int 10h` dengan parameter `AH = 0x0E` untuk _teletype output_. Karakter yang ditampilkan dapat dimasukkan pada register `AL`. Fungsi ini akan menampilkan string karakter ASCII (_null-terminated_) ke layar.
    * untuk `readString`: Implementasi dapat menggunakan fungsi `interrupt` dengan service `int 16h` dengan parameter `AH = 0x00` untuk _keyboard input_. Fungsi ini akan membaca karakter ASCII (_non-control_) yang dimasukkan oleh pengguna dan menyimpannya pada buffer hingga menekan tombol `Enter`. Handle tombol `Backspace` dibebaskan kepada praktikan.
    * untuk `clearScreen`: Ukuran layar adalah `80x25` karakter. Setelah layar dibersihkan, kursor akan kembali ke posisi awal yaitu `(0, 0)` dan buffer video untuk warna karakter diubah ke warna putih. Implementasi dapat menggunakan fungsi `interrupt` dengan service `int 10h` atau menggunakan fungsi `putInMemory` untuk mengisi memori video.
* [shell.c](src/shell.c)
  * Diisi penerapan shell yang menggunakan fungsi kernel untuk parsing keseluruhan command yang diinput

### Headers

* [std_type.h](include/std_type.h)
  * `byte`: unsigned char data type, untuk angka 0-255 (`0x00`-`0xFF`)
  * `bool`: untuk boolean (true/false), karena boolean tidak built-in
* [std_lib.h](include/std_lib.h)
  * `div`: division
  * `mod`: modulo
  * Pembagian dan modulo tidak ada dalam assembly, sehingga harus dilengkapi dengan operator yang tersedia (`+`,`-`,`*`,`<<`,`>>`)
  * `strcmp`: membandingkan dua string
  * `strcpy`: copy string
  * `clear`: fill memory dengan `0`
  * `atoi`: alphanumeric to integer (string menjadi angka)
  * `itoa`: integer to alphanumeric (angka menjadi string)
* [kernel.h](include/kernel.h)
  * Deklarasi header untuk fungsi-fungsi dalam `kernel.c`
* [shell.h](include/shell.h)
  * Deklarasi header untuk fungsi-fungsi dalam `shell.c`

### Makefile

* [makefile](./makefile)
   * `prepare` : membuat disk image baru `floppy.img` pada direktori `bin/` dengan ukuran 1.44 MB.
   * `bootloader` : mengkompilasi `bootloader.asm` menjadi `bootloader.bin` pada direktori `bin/`.
   * `stdlib` : mengkompilasi `std_lib.c` menjadi `std_lib.o` pada direktori `bin/`.
   * `shell`: mengkompilasi `shell.c` menjadi `shell.o` pada direktori `bin/`.
   * `kernel` : mengkompilasi `kernel.c` menjadi `kernel.o` pada direktori `bin/` dan mengkompilasi `kernel.asm` menjadi `kernel_asm.o` pada direktori `bin/`.
   * `link` : menggabungkan `bootloader.bin`, `kernel.o`, `kernel_asm.o`, dan `std_lib.o` menjadi `floppy.img`.
   * `build` : menjalankan perintah `prepare`, `bootloader`, `stdlib`, `kernel`, dan `link`.

### Video Demonstrasi

[Akses Video dalam Assets](./assets/demo.mkv)


## Laporan
### Handling I/O
Dalam menghandle pergerakan kursor, kami menambahkan kode assembly yang berfungsi untuk mendapatkan posisi kursor saat ini, hal ini terdapat pada *kernel.asm*:
```asm
global _getCursorPos

; returns (row << 8) | col
_getCursorPos:
    push bp
    mov bp, sp
    mov ah, 0x03    ; BIOS function to get cursor position
    mov bh, 0x00    ; Page number 0
    int 0x10        ; Call video interrupt
    mov ax, dx      ; Move the result from DX (DH=row, DL=col) to AX for return
    pop bp
    ret
```
Selanjutnya pada kode c untuk input dan output serta clear screen:
```c
void printString(char *str, byte color_attribute) {
  int i = 0;
  int cursor_pos;
  int row, col;

  while (str[i] != '\0') {
    if (str[i] == '\n') {
      interrupt(0x10, (0x0E << 8) | '\r', 0, 0, 0);
      interrupt(0x10, (0x0E << 8) | '\n', 0, 0, 0);
    } else {
      cursor_pos = getCursorPos();
      row = (cursor_pos >> 8) & 0xFF;
      col = cursor_pos & 0xFF;

      interrupt(0x10, (0x0E << 8) | str[i], 0, 0, 0);

      putInMemory(0xB800, (row * 80 + col) * 2 + 1, color_attribute);
    }
    i++;
  }
}
void readString(char *buf, byte color_attribute) {
  int i = 0;
  int ch_code_ax;
  char ch;

  while (1) {
    ch_code_ax = interrupt(0x16, 0x00 << 8, 0, 0, 0);
    ch = (char)ch_code_ax;

    if (ch == 0x0D) { // Enter Key
      buf[i] = '\0';
      interrupt(0x10, (0x0E << 8) | '\r', VIDEO_PAGE << 8, 0, 0);
      interrupt(0x10, (0x0E << 8) | '\n', VIDEO_PAGE << 8, 0, 0);
      break;
    } else if (ch == 0x08) { // Backspace
      if (i > 0) {
        i--;
        interrupt(0x10, (0x0E << 8) | '\b', VIDEO_PAGE << 8, 0, 0);
        interrupt(0x10, (0x0E << 8) | ' ',  VIDEO_PAGE << 8, 0, 0);
        interrupt(0x10, (0x0E << 8) | '\b', VIDEO_PAGE << 8, 0, 0);
      }
    } else if (ch >= ' ' && ch <= '~') { // Printable Character
      if (i < 127) {
        int cursor_pos;
        int row, col;
        
        buf[i] = ch;

        cursor_pos = getCursorPos();
        row = (cursor_pos >> 8) & 0xFF;
        col = cursor_pos & 0xFF;

        interrupt(0x10, (0x0E << 8) | ch, VIDEO_PAGE << 8, 0, 0);

        putInMemory(0xB800, (row * 80 + col) * 2 + 1, color_attribute);

        i++;
      }
    }
  }
}

void clearScreen() {
  interrupt(0x10, (0x06 << 8) | 0x00, (WHITE << 8) | 0x00, (0x00 << 8) | 0x00, (24 << 8) | 79);
  interrupt(0x10, (0x02 << 8) | 0x00, VIDEO_PAGE << 8, 0x00 << 8 | 0x00, 0);
}
```
Dimana untuk print pada screen kita menggunakan interrupt, yang diikuti dengan putInMemory untuk menambahkan warna
### *std_lib*   
Penjelasan untuk tiap fungsi dalam *std_lib.c*:    
- Division (pembagian)
```c
int div(int a, int b) {
  int result;   
  bool negative; 

  if (b == 0) {
    // Division by zero, return 0
    return 0;
  }

  result = 0;
  negative = (a < 0) ^ (b < 0); // XOR check a b negatif atau tidak

  if (a < 0) {
    a = -a;
  }
  if (b < 0) {
    b = -b;
  }

  while (a >= b) {
    a -= b;
    result++;
  }

  return negative ? -result : result;
}
```
Melakukan pembagian secara terus menerus hingga a < b. Serta ada check XOR untuk nilai negatif a dan b, jika a atau b saja yang negatif maka variable *negative* bernilai 1, sedangkan untuk kemungkinan lain, maka akan bernilai 0. Pada bagian return, jika *negative* True atau bernilai 1, maka result akan bernilai negatif, namun (!*negative*) maka akan return result biasa.    

Selanjutnya yaitu mod, atau modulo, modulus:
```c
int mod(int a, int b) {
  if (b == 0) {
    return 0;
  }
  return a - div(a, b) * b;
}
```
Melakukan operasi modulo biasa.     

Selanjutnya yaitu strcmp atu string compare:
```c
bool strcmp(char *str1, char *str2) {
  while (*str1 && (*str1 == *str2)) {
    str1++;
    str2++;
  }
  return (*str1 - *str2); 
}
```
Melakukan pengurangan nilai ASCII dari huruf huruf yang ada di string yang dicek, apabila bernilai 0 maka kedua string identik.    

Selanjutnya ada strcpy atau string copy:
```c
void strcpy(char *dst, char *src) {
  while (*src) {
    *dst++ = *src++;
  }
  *dst = '\0';
}
```
Melakukan while loop hingga pointer src mencapai null terminator, dimana pada tiap iterasi, tiap char dari string src dimasukkan (copy) ke dst atau string destination (tujuan). Saat selesai, maka akan dilakukan penambahan null terminator     

Selanjutnya ada clear:
```c
void clear(byte *buf, unsigned int size) {
  unsigned int i; 
  for (i = 0; i < size; i++) {
    buf[i] = 0;
  }
}
```
Mengisi variable yang dipilih dengan nilai 0 atau mengkosongkannya, agar bisa digunakan untuk menerima input lagi     

Selanjutnya ada atoi:
```c
void atoi(char *str, int *num) {
  int result = 0; 
  int sign = 1;   

  if (*str == '-') {
    sign = -1;
    str++;
  }

  while (*str >= '0' && *str <= '9') {
    result = result * 10 + (*str - '0');
    str++;
  }
  *num = sign * result;
}
```
Mengubah ASCII menjadi integer      

Selanjutnya ada itoa:
```c
void itoa(int num, char *str) {
  int i = 0;   
  int sign = num; 
  int j;       
  char temp;    
  int len;      

  if (sign == 0) {
    str[i++] = '0';
    str[i] = '\0';
    return;
  }

  if (sign < 0) {
    num = -num; 
  }

  while (num > 0) {
    str[i++] = mod(num, 10) + '0'; 
    num = div(num, 10);            
  }

  if (sign < 0) {
    str[i++] = '-';
  }
  str[i] = '\0'; // Null-terminate string

  len = i; 
  j = 0;   
  while (j < div(len, 2)) {
    temp = str[j];
    str[j] = str[len - j - 1];
    str[len - j - 1] = temp;
    j++;
  }
}
```
Mengubah int menjadi ASCII atau string     

Selanjutnya ada strcat:
```c
void strcat(char *dest, char *src) {
  while (*dest) { 
    dest++;
  }

  while (*src) { 
    *dest++ = *src++;
  }
  *dest = '\0'; // Null-terminate the string
}
```
Mirip dengan strcmp, namun pointer dest dimajukan terlebih dahulu hingga akhir lalu ditambahkan dengan string src.
### The Echo (1)
Apapun yang diketik pengguna akan melakukan echo, atau melakukan print kembali, bila itu tidak termasuk *command* yang valid. Hal ini dapat dilakukan dengan meletakkan kode pada *else if* terakhir dari percabangan pilihan, yang dituliskan sebagai berikut:
```c
else if (buf[0] != '\0') {
   printString(buf, color);
   printString("\n", color);
}
```
Dimana akan dilakukan pengecekan terlebih dahulu, jika buffer tidak kosong maka akan melakukan printString buffer dan printString newline
### Yo, Gurt (2)
```c
    else if (strcmp(cmd, "yo") == 0) {
      printString("gurt", color);
      printString("\n", color);
    } else if (strcmp(cmd, "gurt") == 0) {
      printString("yo", color);
      printString("\n", color);
```
Ketika command dari user berupa yo akan print gurt, ketika command berupa gurt akan print yo
### Username (3)
```c
    else if (strcmp(cmd, "user") == 0) {
      if (arg[0][0] == '\0') { 
        strcpy(user, "user");
        printString("Username changed to user\n", color);
      } else {
        if (neutral){
          strcpy(user, arg[0]);
        } else {
          char companyName[64];
          char *iterator = user;
          while (*iterator != '\0' && *iterator != '@'){
            iterator++;
          }

          strcpy(companyName, iterator);
          strcpy(user, arg[0]);
          strcat(user, companyName);
        }
        printString("Username changed to ", color);
        printString(user, color);
        printString("\n", color);
      }
    }
```
Melakukan pengecekan terlebih dahulu apakah command diikuti dengan arg berupa usernam yang diinginkan, jika tidak maka username akan diubah menjadi *user*, selanjutnya dilakukan pengecekan apakah user netral (tidak terafiliasi company), jika iya maka akan langsung mengcopy username baru kedalam variable user. Jika tidak maka akan melakukan operasi yang mengambil suffix company (@company), selanjutnya menimpa variable user dengan username baru, dan variable user akhirnya digabungkan dengan suffix company yang disimpan sebelumnya.    

### Grandcompany (4)
Memungkinkan user bergabung dengan company (menambahkan suffix company di belakang username dari user), perubahan warna terminal, serta melakukan clear screen. Selain itu ditambahkan command clear, yang menghilangkan company suffix pada username user dan mengembalikan warna terminal menjadi putih.
```c
// Define color codes
#define WHITE 0x07
#define RED 0x0C
#define BLUE 0x09
#define YELLOW 0x0E

void pickCompany(char arg[2][64], byte *color, char *user) {
  char baseUser[32]; 
  char *atSymbol;
  int k = 0; 
  int len_base_user; 

  atSymbol = 0; 
  while(user[k] != '\0'){
    if(user[k] == '@'){
      atSymbol = &user[k];
      break;
    }
    k++;
  }

  if (atSymbol != 0) {
    len_base_user = atSymbol - user;
    if (len_base_user > 31) len_base_user = 31; 
    strncpy(baseUser, user, len_base_user);
    baseUser[len_base_user] = '\0';
  } else { 
    strcpy(baseUser, user);
  }


  if (strcmp(arg[0], "maelstrom") == 0) {
    *color = RED;
    strcpy(user, baseUser);
    strcat(user, "@Storm");   
    clearScreen();
  } else if (strcmp(arg[0], "twinadder") == 0) {
    *color = YELLOW; 
    strcpy(user, baseUser);
    strcat(user, "@Serpent");
    clearScreen();
  } else if (strcmp(arg[0], "immortalflames") == 0) {
    *color = BLUE; 
    strcpy(user, baseUser);
    strcat(user, "@Flame");
    clearScreen();
  } else {
    printString("Company itu belum ada...\n", *color);
  }
}
```
Sebelumnya melakukan pengecekan apakah user sudah memiliki suffix suatu company dan jika ada menyimpan baseUserNamenya (username inti tanpa company suffix). Selanjutnya dilakukan pengecekan company yang diinput user, yang jika termasuk dalam daftar nama yang tersedia akan terjadi perubahan warna, dan penambahan suffix company yang dipilih pada baseUserName serta dilanjut dengan clearScreen. Jika tidak ada dalam opsi, maka akan melakukan printString dengan kalimat "Company itu belum ada...". Pemanggilan fungsi ini pada cabang pilihan di fungsi shell adalah sebagai berikut:
```c
else if (strcmp(cmd, "grandcompany") == 0) {
      pickCompany(arg, &color, user); 
      neutral = 0;
}
```
Dimana nilai int neutral yang menandakan user netral (tidak terafiliasi dengan company) menjadi 0 atau false. Selanjutnya untuk kode bagian clear adalah sebagai berikut:
```c
    if (strcmp(cmd, "clear") == 0) {
      char tempUserBase[64];
      char *atSymbolPosition = 0;
      int k = 0;
      int baseNameLength;

      clearScreen();
      color = WHITE;

      while(user[k] != '\0'){
        if(user[k] == '@'){
          atSymbolPosition = &user[k];
          break;
        }
        k++;
      }

      if (!neutral) {
        baseNameLength = atSymbolPosition - user;
        if (baseNameLength < 64) {
            strncpy(tempUserBase, user, baseNameLength);
            tempUserBase[baseNameLength] = '\0';
            strcpy(user, tempUserBase);
        }
      }
      neutral = 1; 
    }
```
Dimana pada fungsi ini akan merubah color menjadi WHITE dan jika tidak netral akan mengubah username menjadi baseUserNamenya saja, selanjutnya di akhir kode aka  mengubah nilai dari neutral menjadi 1 atau True.
### Arithmetics (5)
Melakukan operasi matematika dasar dua angka, yang mampu menghandle input dan output bernilai negatif
```c
    else if (strcmp(cmd, "add") == 0) {
      int a, b, result;
      char str_result[32];
      atoi(arg[0], &a);
      atoi(arg[1], &b);
      result = a + b;
      itoa(result, str_result);
      printString(str_result, color);
      printString("\n", color);
    } else if (strcmp(cmd, "sub") == 0) {
      int a, b, result;
      char str_result[32];
      atoi(arg[0], &a);
      atoi(arg[1], &b);
      result = a - b;
      itoa(result, str_result);
      printString(str_result, color);
      printString("\n", color);
    } else if (strcmp(cmd, "mul") == 0) {
      int a, b, result;
      char str_result[32];
      atoi(arg[0], &a);
      atoi(arg[1], &b);
      result = a * b;
      itoa(result, str_result);
      printString(str_result, color);
      printString("\n", color);
    } else if (strcmp(cmd, "div") == 0) { 
      int a, b, result_val; 
      char str_result[32];
      atoi(arg[0], &a);
      atoi(arg[1], &b);
      result_val = div(a, b); 
      itoa(result_val, str_result);
      printString(str_result, color);
      printString("\n", color);
    }
```
Secara general, untuk arithmetics, akan merubah argumen yang diinput menjadi int, melalui operasi atoi, dan melakukan kalkulasi yang disimpan dalam result, selanjutnya int tersebut diubah kembali menjadi string dengan itoa, dan dilakukan printString. Pada kasus division atau pembagian menggunakan fungsi yang telah disiapkan di *std_lib.c*.
### Yogurt (6)     
Mengeluarkan output random antara tiga kalimat ketika user menginput yogurt
```c
else if (strcmp(cmd, "yogurt") == 0) { 
      unsigned int tick;
      int choice;
      tick = getBiosTick(); // Get BIOS tick count
      choice = mod(tick, 3);  // Get a choice based on tick

      if (choice == 0) {
        printString("gurt> ts unami gng </3\n", color);
      } else if (choice == 1) {
        printString("gurt> yo\n", color);
      } else {
        printString("gurt> sygau\n", color);
      }
}
```
Ketika user mengetik yogurt, maka akan dilakukan randomize berdasarkan hasil modulus BIOS tick dengan 3, yang akan menghasilkan 3 hasil, yaitu 0, 1, 2. Hal ini sesuai dengan jumlah pilihan yang kita miliki yaitu gurt> ts unami gng </3, gurt> yo, dan gurt> sygau.
### Makefile (7)
```makefile
SRC_DIR = src
BIN_DIR = bin
INCLUDE_DIR = include

.PHONY: all clean build prepare bootloader stdlib shell kernel link

all: build

prepare:
	mkdir -p $(BIN_DIR)
	dd if=/dev/zero of=$(BIN_DIR)/floppy.img bs=512 count=2880

bootloader: $(SRC_DIR)/bootloader.asm
	nasm -f bin $(SRC_DIR)/bootloader.asm -o $(BIN_DIR)/bootloader.bin

stdlib: $(SRC_DIR)/std_lib.c $(INCLUDE_DIR)/std_lib.h $(INCLUDE_DIR)/std_type.h
	bcc -ansi -I$(INCLUDE_DIR) -c $(SRC_DIR)/std_lib.c -o $(BIN_DIR)/std_lib.o

shell: $(SRC_DIR)/shell.c $(INCLUDE_DIR)/shell.h $(INCLUDE_DIR)/kernel.h $(INCLUDE_DIR)/std_lib.h $(INCLUDE_DIR)/std_type.h
	bcc -ansi -I$(INCLUDE_DIR) -c $(SRC_DIR)/shell.c -o $(BIN_DIR)/shell.o

kernel: $(SRC_DIR)/kernel.asm $(SRC_DIR)/kernel.c $(INCLUDE_DIR)/kernel.h $(INCLUDE_DIR)/shell.h $(BIN_DIR)/shell.o $(BIN_DIR)/std_lib.o
	nasm -f as86 $(SRC_DIR)/kernel.asm -o $(BIN_DIR)/kernel-asm.o
	bcc -ansi -I$(INCLUDE_DIR) -c $(SRC_DIR)/kernel.c -o $(BIN_DIR)/kernel.o
	# Link kernel.o, kernel-asm.o, shell.o, and std_lib.o together
	# This was the main correction needed for linking all parts of the kernel.
	ld86 -o $(BIN_DIR)/kernel.bin -d $(BIN_DIR)/kernel.o $(BIN_DIR)/kernel-asm.o $(BIN_DIR)/shell.o $(BIN_DIR)/std_lib.o

link: $(BIN_DIR)/bootloader.bin $(BIN_DIR)/kernel.bin $(BIN_DIR)/floppy.img
	dd if=$(BIN_DIR)/bootloader.bin of=$(BIN_DIR)/floppy.img bs=512 count=1 conv=notrunc
	dd if=$(BIN_DIR)/kernel.bin of=$(BIN_DIR)/floppy.img bs=512 seek=1 conv=notrunc

clean:
	rm -f $(BIN_DIR)/*.o $(BIN_DIR)/*.bin $(BIN_DIR)/floppy.img

build: prepare bootloader stdlib shell kernel link
```
Melakukan compile seperti biasa untuk tiap bagian kode, dengan tambahan -I directory *include* agar header files ikut terbaca dalam proses compile. Lalu pada bagian akhir compiling kernel, menggunakan ld86 yang melakukan link *kernel.o, kernel-asm.o, shell.o dan std_lib.o* menjadi satu file berupa *kernel.bin*.
