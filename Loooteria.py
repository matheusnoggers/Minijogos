import random

variavel=[random.randint(0,60), random.randint(0,60), random.randint(0,60), random.randint(0,60), random.randint(0,60), random.randint(0,60)]

print("Insira os numeros da sua aposta: ")
global aposta
aposta=[]

def recurso():
    ap=int(input())
    if ap>=0 and ap<=60:
        aposta.append(ap)
    else:
        print("O numero nao pode ser validado porque nao esta entre 0 e 60")
        recurso()

for i in range(6):
    recurso()

if aposta==variavel:
    print("Voce ganhou dois milhoes de reais!")
else:
    print("Voce errou! =(")

print("Sua aposta: ", aposta)
print("Numeros da loteria: ", variavel)