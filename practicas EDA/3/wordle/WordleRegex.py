import re

filename = r'C:\Users\chapv\OneDrive\Escritorio\Jflap\3\wordle\0_palabras_todas.txt'

with open(filename, encoding="utf8") as file:
    # lines = file.readlines()
    print("Leidas todas la palabras del español correctamente")
    data = file.read()
    # close file
    file.close()

# Nos quedaremos solo con las que cumplen el regex que indique 5 caracteres

regex_cinco_caracteres = r'\b[a-záéíóú]{5}\b'
palabras_cinco_letras = re.findall(regex_cinco_caracteres, data, re.MULTILINE)

#cumplen primeras condiciones 
regex_intento = re.compile(r'^[^CNS]E[^CN]A[^CN]$', re.IGNORECASE)

def cumple(palabra):
    return(
        regex_intento.match(palabra)
        and
        's' in palabra and palabra[0]!='s'
    )
filtradas = list(filter(cumple,palabras_cinco_letras))

print(f"Posibles palabras:{len(filtradas)}")
print(filtradas)

