import re
import json

def extraer_ing(texto):
    patron = re.compile(
        r'(\d+)\s*(g(?:ramos)?|ml|l(?:itros)?)\s*de\s*([\w\s]+?)(?=,|\.|y|$)',
        re.IGNORECASE
    )
    coincidencias = patron.findall(texto)
    ingredientes=[]
    for cantidad, unidad, nombre in coincidencias:
        ingredientes.append(
            {
                "nombre":nombre.strip().lower(),
                "cantidad":int(cantidad),
                "unidad":unidad.lower()
            }
        )
    return {"ingredientes":ingredientes}

texto="".join(["Para preparar mi sopa, necesito 1 litro de caldo","y 200 gramos de fideos"])
res=extraer_ing(texto)
print("Salida estructurada de JSON:\n")
print(json.dumps(res,indent=2,ensure_ascii=False))