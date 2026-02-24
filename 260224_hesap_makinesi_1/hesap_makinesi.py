def topla(a, b):
    return a + b

def cikar(a, b):
    return a - b

def carp(a, b):
    return a * b

def bol(a, b):
    if b == 0:
        return "Hata: Sıfıra bölünemez!"
    return a / b

def main():
    print("=== Hesap Makinesi ===")
    print("1. Toplama")
    print("2. Çıkarma")
    print("3. Çarpma")
    print("4. Bölme")
    print("5. Çıkış")

    while True:
        secim = input("\nİşlem seçin (1-5): ")

        if secim == "5":
            print("Güle güle!")
            break

        if secim in ["1", "2", "3", "4"]:
            sayi1 = float(input("Birinci sayı: "))
            sayi2 = float(input("İkinci sayı: "))

            if secim == "1":
                sonuc = topla(sayi1, sayi2)
            elif secim == "2":
                sonuc = cikar(sayi1, sayi2)
            elif secim == "3":
                sonuc = carp(sayi1, sayi2)
            elif secim == "4":
                sonuc = bol(sayi1, sayi2)

            print(f"Sonuç: {sonuc}")
        else:
            print("Geçersiz seçim!")

if __name__ == "__main__":
    main()
