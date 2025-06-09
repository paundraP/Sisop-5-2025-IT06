# Sisop-5-2025-IT-Template

## Kelompok

| Nama                    | NRP        |
| ----------------------- | ---------- |
| Paundra Pujo Darmawan   | 5027241008 |
| Putri Joselina Silitonga | 5027241116 |

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

   - `user <username>` = mengubah username menjadi `<username>`
   - `user` = mengubah username menjadi default `user`

   Ilustrasi:

   ```
   user> user Tia
   Username changed to Tia
   Tia> user
   Username changed to user
   user>
   ```

4. Tiga negara besar dari Eorzean Alliance butuh bantuan anda untuk ikut serta dalam "Grand Company" mereka sehingga anda bisa mengubah warna terminal ajaib anda sesuai warna utama dari company mereka:

   - `grandcompany maelstrom` = clear terminal, ubah semua teks berikutnya jadi merah
   - `grandcompany twinadder` = clear terminal, ubah semua teks berikutnya jadi kuning
   - `grandcompany immortalflames` = clear terminal, ubah semua teks berikutnya jadi biru
   - `grandcompany <selain atau kosong>` = tunjukkan error message
   - `clear` = clear terminal, ubah semua teks berikutnya kembali jadi awal (para Grand Company sedih kamu netral)

   Selain mengubah seluruh warna terminal, nama anda di dalam terminal akan diberikan tambahan nama judul Grand Company:

   - Maelstrom = `user@Storm`
   - Twin Adder = `user@Serpent`
   - Immortal Flames = `user@Flame`
   - `clear` = menghapus nama grand company

   Ilustrasi:

   ```
   gurt> grandcompany maelstrom
   -- terminal clear menjadi warna merah --
   gurt@Storm> clear
   -- terminal clear menjadi warna putih --
   ```

5. Sebagai pahlawan terkenal di antara ketiga negara besar Eorzean Alliance, salah satu supplier senjata terbesar di seluruh Eorzea bernama "Rowena's House of Splendors" tiba-tiba memerlukan bantuan anda untuk membuat sebuah sistem kalkulator sederhana melalui command karena pemimpin mereka tertidur setelah mengurus semua orang di dalam Eorzea:

   - `add <x> <y>` = x + y
   - `sub <x> <y>` = x - y
   - `mul <x> <y>` = x \* y
   - `div <x> <y>` = x / y

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

   - `yo`
   - `ts unami gng </3`
   - `sygau`

   pilih secara _random_

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

- [kernel.asm](src/kernel.asm)
  - `_putInMemory`: penjelasan terdapat dalam modul
  - `_interrupt`: fungsi untuk interrupt
    - `number`: interrupt vector number
    - `AX`,`BX`,`CX`,`DX`: register untuk diisi
    - `AX` merupakan kombinasi dari `AH` dan `AL`, pola ini juga berlaku untuk `BX`,`CX`, dan `DX`
    - Untuk menggabungkan jenis register `H` dan `L` menjadi `X` bisa menggunakan salah satu metode berikut:
      ```c
      AX = AH << 8 | AL    // first method
      AX = AH * 256 + AL   // second method
      ```
  - `getBiosTick`: fungsi untuk mendapatkan tick dari BIOS
- [kernel.c](src/kernel.c)
  - Diisi penerapan fungsi `printString`, `readString`, dan `clearScreen` dengan bantuan `kernel.asm`
    - untuk `printString`: Implementasi dapat menggunakan fungsi `interrupt` dengan service `int 10h` dengan parameter `AH = 0x0E` untuk _teletype output_. Karakter yang ditampilkan dapat dimasukkan pada register `AL`. Fungsi ini akan menampilkan string karakter ASCII (_null-terminated_) ke layar.
    - untuk `readString`: Implementasi dapat menggunakan fungsi `interrupt` dengan service `int 16h` dengan parameter `AH = 0x00` untuk _keyboard input_. Fungsi ini akan membaca karakter ASCII (_non-control_) yang dimasukkan oleh pengguna dan menyimpannya pada buffer hingga menekan tombol `Enter`. Handle tombol `Backspace` dibebaskan kepada praktikan.
    - untuk `clearScreen`: Ukuran layar adalah `80x25` karakter. Setelah layar dibersihkan, kursor akan kembali ke posisi awal yaitu `(0, 0)` dan buffer video untuk warna karakter diubah ke warna putih. Implementasi dapat menggunakan fungsi `interrupt` dengan service `int 10h` atau menggunakan fungsi `putInMemory` untuk mengisi memori video.
- [shell.c](src/shell.c)
  - Diisi penerapan shell yang menggunakan fungsi kernel untuk parsing keseluruhan command yang diinput

### Headers

- [std_type.h](include/std_type.h)
  - `byte`: unsigned char data type, untuk angka 0-255 (`0x00`-`0xFF`)
  - `bool`: untuk boolean (true/false), karena boolean tidak built-in
- [std_lib.h](include/std_lib.h)
  - `div`: division
  - `mod`: modulo
  - Pembagian dan modulo tidak ada dalam assembly, sehingga harus dilengkapi dengan operator yang tersedia (`+`,`-`,`*`,`<<`,`>>`)
  - `strcmp`: membandingkan dua string
  - `strcpy`: copy string
  - `clear`: fill memory dengan `0`
  - `atoi`: alphanumeric to integer (string menjadi angka)
  - `itoa`: integer to alphanumeric (angka menjadi string)
- [kernel.h](include/kernel.h)
  - Deklarasi header untuk fungsi-fungsi dalam `kernel.c`
- [shell.h](include/shell.h)
  - Deklarasi header untuk fungsi-fungsi dalam `shell.c`

### Makefile

- [makefile](./makefile)
  - `prepare` : membuat disk image baru `floppy.img` pada direktori `bin/` dengan ukuran 1.44 MB.
  - `bootloader` : mengkompilasi `bootloader.asm` menjadi `bootloader.bin` pada direktori `bin/`.
  - `stdlib` : mengkompilasi `std_lib.c` menjadi `std_lib.o` pada direktori `bin/`.
  - `shell`: mengkompilasi `shell.c` menjadi `shell.o` pada direktori `bin/`.
  - `kernel` : mengkompilasi `kernel.c` menjadi `kernel.o` pada direktori `bin/` dan mengkompilasi `kernel.asm` menjadi `kernel_asm.o` pada direktori `bin/`.
  - `link` : menggabungkan `bootloader.bin`, `kernel.o`, `kernel_asm.o`, dan `std_lib.o` menjadi `floppy.img`.
  - `build` : menjalankan perintah `prepare`, `bootloader`, `stdlib`, `kernel`, dan `link`.

### Video Demonstrasi

[Akses Video dalam Assets](./assets/demo.mp4)

https://github.com/user-attachments/assets/1cfa66b1-b2f5-4e3e-a4b2-ec8b012f6fbb

## Laporan

# Laporan Praktikum Sistem Operasi Modul 5 
## EorzeOS

---

## Soal 1 - Echo

Pada soal ini, kita diminta mengimplementasikan fitur **"The Echo"**, yaitu kemampuan untuk mengulang setiap input pengguna yang *bukan merupakan perintah* (command) yang dikenali oleh shell EorzeOS.

Jika pengguna mengetik sesuatu yang tidak dikenali, maka shell akan mencetak ulang input tersebut.

###  Implementasi

Fitur ini ditangani dalam fungsi `processCommand()` di `shell.c`. Di akhir fungsi terdapat blok `else` sebagai fallback:

```c
else {
    printString(rawInput);
}
```

#### Fungsi shell() memanggil:

1. `displayPrompt()` : menampilkan prompt user> atau username@Host>.

2. `readString()` : membaca input pengguna.

3. `parseCommand()`:  memisahkan nama command dan argumennya.

4. `processCommand()`: mengevaluasi dan mengeksekusi command.

Jika command tidak dikenali (strcmp() gagal untuk semua kasus if sebelumnya), maka jatuh ke blok else, dan input dikembalikan ke layar melalui printString().

Output: 

```
user> Hello!
Hello!
user> I have the Echo
I have the Echo
```

## 2. Soal 2 - yo / gurt
Soal ini meminta kita untuk mengimplementasikan command sederhana yang saling membalas satu sama lain:

Jika pengguna mengetik `yo`, maka shell membalas dengan `gurt`.
Jika pengguna mengetik `gurt`, maka shell membalas dengan `yo`.

#### Implementasi
Fitur ini di-handle dalam fungsi processCommand() pada file shell.c. Implementasinya cukup langsung menggunakan strcmp() untuk membandingkan input dengan string "yo" dan "gurt":
```
if (strcmp(command, "yo")) {
    printString("gurt\r\n");
    
} else if (strcmp(command, "gurt")) {
    printString("yo\r\n");
}
```
Alur: 
1. Input pengguna diambil oleh `readString()`.

2. Command diproses di `parseCommand()`, dan yo atau gurt dimasukkan ke parameter command.

3. Fungsi `processCommand()` melakukan pencocokan string:

4. Jika cocok dengan `yo`, cetak `gurt`.
Jika cocok dengan `gurt`, cetak `yo`.

```user> yo
gurt
user> gurt
yo
```

### Soal 3 - Command user 
EorzeOS harus mendukung command untuk mengganti nama user. Bentuk command-nya:

#### user <username> → mengubah username ke nama yang diberikan.

#### user → mengembalikan username ke default yaitu user.

#### Implementasi
Logika command ini ada di fungsi `processCommand()` dalam file shell.c. Pada blok else if (strcmp(command, "user")), program memeriksa apakah ada argumen yang diberikan:
```
} else if (strcmp(command, "user")) {
    if (arguments[0][0] == '\0') {
        strcpy(currentUser, "user");
    } else {
        strcpy(currentUser, arguments[0]);
    }
    printString("Username changed to ");
    printString(currentUser);
    printString("\r\n");
}
```
`currentUser` menyimpan nama user aktif dan digunakan di prompt shell. Jika argumen kosong, nama di-reset ke "user".
```
user> user Tia
Username changed to Tia
Tia> user
Username changed to user
user>
```
### Soal 4 - Command grandcompany 
EorzeOS harus bisa mengubah warna terminal dan hostname berdasarkan nama `Grand Company`. Terdapat tiga opsi:

`grandcompany maelstrom` → teks jadi merah, hostname jadi @Storm.

`grandcompany twinadder` → teks jadi kuning, hostname jadi @Serpent.

`grandcompany immortalflames` → teks jadi biru, hostname jadi @Flame.

`clear` → reset ke warna dan hostname default.

#### Implementasi
Di processCommand(), saat command adalah grandcompany, argumen dicek untuk menentukan warna dan host:

```
} else if (strcmp(command, "grandcompany")) {        
    if (strcmp(arguments[0], "maelstrom")) {  
        updateDisplayColor(0x0c);   // merah
        clearScreen(displayColor);                       
        strcpy(systemHost, "@Storm");            
    } else if (strcmp(arguments[0], "twinadder")) {   
        updateDisplayColor(0x0e);   // kuning
        clearScreen(displayColor);             
        strcpy(systemHost, "@Serpent");            
    } else if (strcmp(arguments[0], "immortalflames")) {       
        updateDisplayColor(0x09);   // biru
        clearScreen(displayColor);             
        strcpy(systemHost, "@Flame");                   
    } else {
        printString("Unknown company\r\n");
    }
}
```
Untuk reset, ada command clear:
```
} else if (strcmp(command, "clear")) {
    strcpy(systemHost, "");
    updateDisplayColor(0x07);  // putih
    clearScreen(displayColor);
}
```
Contoh:
```
user> grandcompany maelstrom
-- terminal merah --
user@Storm>

user@Storm> clear
-- terminal putih --
user>
```

### Soal 5 - Kalkulator (add, sub, mul, div)
EorzeOS diminta membuat sistem kalkulator sederhana melalui command:

`add <x> <y>` → hasil penjumlahan x + y

`sub <x> <y>` → hasil pengurangan x - y

`mul <x> <y>` → hasil perkalian x * y

`div <x> <y>` → hasil pembagian x / y (dengan penanganan pembagi nol)

#### Implementasi
Fungsi ini di-handle melalui else if dalam processCommand() pada shell.c, menggunakan fungsi `atoi()` untuk parsing dan `itoa()` untuk konversi hasil.

Implementasi add:
```
} else if (strcmp(command, "add")) {
    if (arguments[0][0] == '\0' || arguments[1][0] == '\0') {
        printString("Usage: add <num1> <num2>\r\n");
        return;
    }
    atoi(arguments[0], &firstNum);
    atoi(arguments[1], &secondNum);
    calculationResult = firstNum + secondNum;
    itoa(calculationResult, resultString);        
    printString(resultString);
    printString("\r\n");
}
```
Untuk pembagian (div), ditambahkan pengecekan pembagi nol:
```
if (secondNum == 0) {
    printString("Error: Division by zero\r\n");
    return;
}
```
Contoh
```
user> add 4 5
9

user> sub 10 3
7

user> mul 2 -8
-16

user> div 10 0
Error: Division by zero
```

### Soal 6 - Command yogurt 
EorzeOs harus menghasilkan respons acak ketika pengguna mengetikkan yogurt. Jawaban bisa berupa salah satu dari:
```
yo

ts unami gng </3

sygau
```

Respons akan diawali oleh prompt gurt>.

#### Implementasi
Saat command yogurt terdeteksi di processCommand(), program memanggil `generateRandomResponse()`, dengan prefix prompt "gurt":
```
} else if (strcmp(command, "yogurt")) {
    displayPrompt("gurt");
    generateRandomResponse();    
}
```
#### Isi dari generateRandomResponse():
```
int randomValue = mod(getBiosTick(), 3);

switch(randomValue) {
    case 0:
        printString("ts unami gng </3\r\n");
        break;
    case 1:
        printString("yo\r\n");
        break;
    default:
        printString("sygau\r\n");
        break;
}
```
Fungsi `getBiosTick()` mengambil waktu BIOS tick, lalu dimod 3 agar hasil random berada pada range 0–2.
```
user> yogurt
gurt> yo
user> yogurt
gurt> ts unami gng </3
user> yogurt
gurt> sygau
```

### Soal 7 - Makefile
EorzeOS perlu dilengkapi dengan `Makefile` agar dapat dikompilasi secara otomatis dengan command make. Makefile harus menyatukan semua komponen: bootloader, kernel, shell, dan pustaka standar.
#### Implementasi
File Makefile yang digunakan menyediakan beberapa target:

### Tahapan build:
```
build: prepare bootloader stdlib shell kernel link
```
#### Rincian langkah:
`prepare` : membuat image floppy kosong
```
dd if=/dev/zero of=bin/floppy.img bs=512 count=2880
```
`bootloader:` compile bootloader.asm → bootloader.bin

`stdlib:` compile std_lib.c

`shell:` compile shell.c

`kernel:` compile kernel.c dan kernel.asm

`link:` gabungkan semua object menjadi kernel.bin, lalu tulis ke sektor floppy.img

Command:
```
make all     # membersihkan & membuild ulang semua
make clean   # menghapus file hasil build
``` 
Isi Makefile: 
```
CFLAGS = -ansi -Iinclude

prepare:
	dd if=/dev/zero of=bin/floppy.img bs=512 count=2880

bootloader:
	nasm -f bin src/bootloader.asm -o bin/bootloader.bin
	dd if=bin/bootloader.bin of=bin/floppy.img bs=512 count=1 conv=notrunc

stdlib:
	bcc $(CFLAGS) -c src/std_lib.c -o bin/std_lib.o

shell:
	bcc $(CFLAGS) -c src/shell.c -o bin/shell.o

kernel:
	nasm -f as86 src/kernel.asm -o bin/kernel-asm.o
	bcc $(CFLAGS) -c src/kernel.c -o bin/kernel.o
	
link:
	ld86 -o bin/kernel.bin -d bin/kernel.o bin/kernel-asm.o  bin/std_lib.o bin/shell.o
	dd if=bin/kernel.bin of=bin/floppy.img bs=512 seek=1 conv=notrunc


build: prepare bootloader stdlib shell kernel link

clean:
	rm -f bin/*

all: clean build
```














