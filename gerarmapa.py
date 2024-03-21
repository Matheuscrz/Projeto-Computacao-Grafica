import random
import math

def generate_gradient_ppm_binary(width, height):
    """Gera um arquivo PPM binário (tipo P6) com um mapa de relevo mais complexo."""
    ppm_header = f"P6\n{width} {height}\n255\n"
    ppm_data = bytearray()

    for y in range(height):
        for x in range(width):
            # Gera um relevo mais complexo com base em funções matemáticas
            value = int((math.sin(x / 100) + math.sin(y / 100)) * 128 + 128)
            # Limita os valores entre 0 e 255
            value = max(0, min(value, 255))
            # Adiciona o valor aos dados do arquivo
            ppm_data.extend([value, value, value])

    with open("mapa.ppm", "wb") as ppm_file:
        # Escreve o cabeçalho
        ppm_file.write(ppm_header.encode())
        # Escreve os dados
        ppm_file.write(ppm_data)

# Dimensões do mapa
width = 800
height = 600
# Gera o arquivo PPM binário
generate_gradient_ppm_binary(width, height)
print("Arquivo PPM binário gerado com sucesso: mapa.ppm")
