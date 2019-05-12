# FP_SISOP19_A05

FUSE AND THREAD

Nama : Chaniyah Zulfa M (05111740000115) <br>
        Faqih Fathan I. (05111740000175)

Buatlah sebuah music player dengan bahasa C yang memiliki fitur play nama_lagu, pause, next, prev, list lagu. Selain music player juga terdapat FUSE untuk mengumpulkan semua jenis file yang berekstensi .mp3 kedalam FUSE yang tersebar pada direktori /home/user. Ketika FUSE dijalankan, direktori hasil FUSE hanya berisi file .mp3 tanpa ada direktori lain di dalamnya. Asal file tersebut bisa tersebar dari berbagai folder dan subfolder. program mp3 mengarah ke FUSE untuk memutar musik. Note: playlist bisa banyak, link mp3player

# jawaban
Ada dua file.c yang akan digunakan untuk menyelesaikan msalah ini.

1.Code fus.c = Code yang outputnya berupa File system yang dapat memuat semua jenis file .mp3 yang didapatkan dari direktori yang menyebar dari /home/chaniyahzm atau kedalam folder folder maupun subfolder didalamnya.

2.Code mp3.c = Code yang memuat fungsi-fungsi mp3 yang dibutuhkan. Ada fungsi playmusic,listmusic,prev,next,pause

---FUSE---

Fungsi yang dibutuhkan :
        > xmp_getattr untuk mengambil atribut
        > xmp_read untuk membaca file
        > xmp_readdir untuk membaca direktori
        > xmp_write untuk mengedit file
        > xmp_mknod untuk membuat file yang tertentu yang diinginkan

---MP3---
