Projenin geliştirme sürecinde ilk olarak FreeRTOS POSIX altyapısı kurularak giris.txt dosyasından görev parametrelerini ayrıştıran bir yapı oluşturulmuş, 
ardından gerçek zamanlı görevler için FCFS ve kullanıcı görevleri için üç seviyeli geri beslemeli kuyruk (MLFQ) mekanizması vTaskSuspend ve vTaskResume komutlarıyla entegre edilmiştir;
her saniye sonunda görevlerin öncelik değişimleri ve zaman kuantumu yönetimleri yapılandırıldıktan sonra, tüm sürecin dinamik renkli terminal çıktıları ve performans 
analizlerini içeren raporun hazırlanmasıyla simülasyon tamamlanmıştır.
