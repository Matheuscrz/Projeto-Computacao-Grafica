import random

def generate_color():
    """Gera uma cor aleatória."""
    return random.randint(0, 255), random.randint(0, 255), random.randint(0, 255)

def generate_gradient_ppm(width, height):
    """Gera um arquivo PPM com um mapa de relevo com transição gradual dos valores."""
    ppm_header = f"P6\n{width} {height}\n255\n"
    ppm_data = ""
    
    for y in range(height):
        for x in range(width):
            # Gera uma cor aleatória para simular o relevo gradual
            color = generate_color()
            # A intensidade da cor é baseada na posição do pixel
            intensity = int((x / width) * 255)
            # Aplica a intensidade à cor gerada
            color = tuple(min(c + intensity, 255) for c in color)
            # Formata a cor para o formato PPM e adiciona aos dados do arquivo
            ppm_data += " ".join(map(str, color)) + " "
        ppm_data += "\n"
    
    with open("mapa.ppm", "w") as ppm_file:
        ppm_file.write(ppm_header + ppm_data)

# Dimensões do mapa
width = 800
height = 600
# Gera o arquivo PPM
generate_gradient_ppm(width, height)
print("Arquivo PPM gerado com sucesso: mapa.ppm")
