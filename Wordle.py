import random as rand

list=["TERMO", "MUMIA", "ALCES", "BUGIO", "ZEBRA", "BRASA", "ALTOS", "BURRO", "CELTA", "PENSO", "LENTO", "GENTE"]
word=rand.choice(list)

print("""WORDLE!
Feito por Matheus Nogueira""")

for i in range(6):
    print(f"{6-i} tentativas restantes.")
    choice=input("Insira sua palavra: ")
    
    choice=choice.upper()
    
    if(choice==word):
        break
    
    while len(choice)>5:
        choice=input("Inválido, insira outra: ")
        
    for l in range(5):
        if choice[l] in word:
            to_print=choice[l]+" está na palavra "
            if choice[l]==word[l]:
                to_print+="no local correto"
        else:
            to_print=choice[l]+" não está na palavra"
        print(to_print)
    
if word==choice:
    print("Meus parabéns, você venceu!")
else:
    print(f"Você errou! A palavra era {word}")