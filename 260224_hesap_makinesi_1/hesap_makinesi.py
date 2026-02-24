import math

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

def us_al(a, b):
    return a ** b

def karekok(a):
    if a < 0:
        return "Hata: Negatif sayının karekökü alınamaz!"
    return math.sqrt(a)

def faktoriyel(a):
    if a < 0 or a != int(a):
        return "Hata: Faktöriyel sadece pozitif tam sayılar için!"
    return math.factorial(int(a))

def sinus(a):
    return math.sin(math.radians(a))

def kosinus(a):
    return math.cos(math.radians(a))

def tanjant(a):
    return math.tan(math.radians(a))

def logaritma(a):
    if a <= 0:
        return "Hata: Logaritma sadece pozitif sayılar için!"
    return math.log10(a)

def dogal_log(a):
    if a <= 0:
        return "Hata: Logaritma sadece pozitif sayılar için!"
    return math.log(a)

def mutlak_deger(a):
    return abs(a)

def main():
    print("=== Bilimsel Hesap Makinesi ===")
    print("\n-- Temel İşlemler --")
    print("1. Toplama")
    print("2. Çıkarma")
    print("3. Çarpma")
    print("4. Bölme")
    print("5. Üs alma (a^b)")
    print("\n-- Bilimsel İşlemler --")
    print("6. Karekök")
    print("7. Faktöriyel")
    print("8. Sinüs (derece)")
    print("9. Kosinüs (derece)")
    print("10. Tanjant (derece)")
    print("11. Logaritma (log10)")
    print("12. Doğal logaritma (ln)")
    print("13. Mutlak değer")
    print("\n-- Sabitler --")
    print("14. Pi sayısı")
    print("15. Euler sayısı (e)")
    print("\n0. Çıkış")

    while True:
        secim = input("\nİşlem seçin (0-15): ")

        if secim == "0":
            print("Güle güle!")
            break

        if secim in ["1", "2", "3", "4", "5"]:
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
            elif secim == "5":
                sonuc = us_al(sayi1, sayi2)

            print(f"Sonuç: {sonuc}")

        elif secim in ["6", "7", "8", "9", "10", "11", "12", "13"]:
            sayi = float(input("Sayı: "))

            if secim == "6":
                sonuc = karekok(sayi)
            elif secim == "7":
                sonuc = faktoriyel(sayi)
            elif secim == "8":
                sonuc = sinus(sayi)
            elif secim == "9":
                sonuc = kosinus(sayi)
            elif secim == "10":
                sonuc = tanjant(sayi)
            elif secim == "11":
                sonuc = logaritma(sayi)
            elif secim == "12":
                sonuc = dogal_log(sayi)
            elif secim == "13":
                sonuc = mutlak_deger(sayi)

            print(f"Sonuç: {sonuc}")

        elif secim == "14":
            print(f"Pi = {math.pi}")

        elif secim == "15":
            print(f"e = {math.e}")

        else:
            print("Geçersiz seçim!")

if __name__ == "__main__":
    main()
