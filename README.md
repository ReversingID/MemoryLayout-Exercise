# Memory-Layout Exercise

Open repository for structure and layout of object in memory for reverse engineering purpose.

### Selayang Pandang

Repository ini digunakan untuk menghimpun informasi dan pengetahuan tentang representasi objek di memory dan mekanisme yang berhubungan dengannya. Beberapa contoh binary disertakan di dalam repository sebagai latihan untuk memperdalam konsep.

Repository ini merupakan repository bebas dan terbuka. Siapapun, baik internal maupun eksternal komunitas Reversing.ID, dapat mengakses dan memanfaatkan konten ini.

### Representasi Objek

Setiap objek yang diinstansiasi akan menempati ruang memory. Besarnya ruang memory yang dialokasikan bergantung kepada banyaknya variabel (field) yang dideklarasikan serta metadata dari class. Beberapa bahasa dan compiler mungkin merepresentasikan objek dengan cara berbeda atau memiliki karakteristik tertentu.

### Struktur dan Konten 

Repository ini terbagi menjadi beberapa direktori sesuai dengan bahasa pemrograman yang digunakan. Masing-masing bahasa memiliki representasi yang berbeda sehingga pembahasan perlu dilakukan spesifik terhadap bahasa tersebut.

Di setiap direktori akan terdapat beberapa direktori yang akan melakukan pembahasan secara spesifik terhadap suatu teknis tertentu. Beberapa topik yang menjadi cakupan pembahasan antara lain:

* memory layout
* object-creation dan object-destruction
* instantiation order
* vtable (virtual table) atau vmt (virtual method table)
* Run-Time Type Identifier

### Exercise

Setiap sample merupakan sebuah exercise dengan objektif tertentu. Masing-masing sample akan memiliki instruksi untuk melakukan kompilasi dan beberapa pertanyaan yang harus dijawab saat melakukan analisis. Gunakan source code sebagai perbandingan untuk mengidentifikasi field yang sesuai.

Setiap sample akan melakukan dump raw binary saat runtime. Dump dilakukan terhadap objek dan struktur terkait class di memory. Objektif dari setiap exercise adalah mengenali layout memory dari setiap objek melalui analisis dump.

Analisis dapat pula dilakukan dengan melakukan debugging.

### Bagaimana Cara Berkontribusi?

Ini adalah projek terbuka.

Kamu bisa memberikan sumbangan berupa kode yang berkaitan dengan implementasi bahasa tertentu, baik yang telah ada maupun belum dicakup dalam repository ini. Kamu juga bisa memberikan referensi=referensi terkait yang bisa digunakan untuk menambah pemahaman terhadap materi.

Yang dapat kamu lakukan:

- melakukan pull request.
- mengirimkan email ke pengurus [at] reversing.id
- memberi tahu di telegram @ReversingID

Diharapkan agar segala referensi yang ada menggunakan Bahasa Indonesia sebagai sarana penyampaian informasi.