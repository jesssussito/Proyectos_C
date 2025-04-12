import re

def formacion(palabra,letras):
    letras=list(letras)
    for letra in palabra:
        if(letra in letras):
            letras.remove(letra)
        else:
            return False
    return True


def main():
    letras = input("[+] Introduzca las 9 letras(sin espacios)\n").strip()
    if(len(letras)!=9):
        print("[!] Debes introduccir 9 letras.\n")
        return
    filename=r'C:\Users\chapv\OneDrive\Escritorio\Jflap\3\wordle\0_palabras_todas.txt'
    with open(filename, encoding="utf8") as file:
        print("Leidas todas la palabras del español correctamente.\n")
        data = file.read()
        # close file
        file.close()# lines = file.readlines()
    regex_nueve_caracteres = r'\b[a-záéíóú]{1,9}\b'
    regex_valida=re.compile(regex_nueve_caracteres,re.IGNORECASE)
    todas = data.splitlines()
    validas=[p for p in todas if regex_valida.fullmatch(p)]
    formables=[p for p in validas if formacion(p,letras)]
    if not formables:
        print(f"Con las siguientes letras {letras} no se puede formar ninguna palabra.\n")
        return
    max_len =max(len(p) for p in formables)
    palabras_maximas=[p for p in formables if len(p)==max_len]
    palabras_maximas.sort(reverse=True)
    print(f"Palabra/s de mayor longitud ({max_len} letras) que se pueden formar:")
    for p in palabras_maximas:
        print(p)
        print("\n")
if __name__ == "__main__":
    main()