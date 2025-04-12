# requests for fetching html of website
import requests
# re biblioteca de regular expressions
import re

# OPCIÓN 1: OBTENINENDO EL HTML CON UNA PETICIÓN

# Obtener HTML (web no dinámica)
# https://www.clickgasoil.com/m/precio-de-gasolina-95-salamanca
r = requests.get('https://www.clickgasoil.com/m/precio-de-gasolina-95-salamanca')

# Extraer el cotenido como texto
data = r.text

# Descomentar esta linea para ver el contenido obtenido y llevarlo a https://regex101.com/
# O utilizar el inspector de elementos de Google Chrome para obtener el código fuente de la página web
#print(data)

# TIP: En regex101 tenéis una opción para generar el código para lenguaje de programación que necesitéis


# OPCIÓN 2: Obtener el codigo HTML del inspector de elementos de Google Chrome para obtener el código fuente de la página web
#data = """  CODIGO HTML COPIADO   """


# COMPLETA ESTO
# Las expresiones regulares en Python tienen una r detras que significa raw string, 
# lo que significa que cualquier carácter especial dentro de la cadena de texto se
# interpreta literalmente en lugar de como un carácter de escape.
regex = r"<span>RONDA OESTE</span>.*?<td>(\d{1}\.\d{3})"


# Cuidado con los flags
# Prueba a utilizar caputuring groups
# Comprueba que ocurre con findall, match, search etc.
"""

findall documentación
https://docs.python.org/3/library/re.html#re.findall
The result depends on the number of capturing groups in the pattern. 
If there are no groups, return a list of strings matching the whole pattern. 
If there is exactly one group, return a list of strings matching that group. 
If multiple groups are present, return a list of tuples of strings matching the groups. 
Non-capturing groups do not affect the form of the result.

"""
precio_gasolina = re.findall(regex, data, re.MULTILINE)
print(precio_gasolina)


if len(precio_gasolina) > 0:
	print(f"El precio de la gasolina es: {precio_gasolina[0]}")

