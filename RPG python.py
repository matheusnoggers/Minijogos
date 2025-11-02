import random
import os

global name_list
name_list=["Malaquias","Papa-Papaya","Jeremias","Astolfo"]
class Player:
    def __init__(self, name):
        self._name=name
        self.hp=100
        self._resistance=12
        self._strength=10

    def attack(self):
        print(f"{self._name} tenta realizar um ataque!")
        return random.randint(1, self._strength)+self._strength
    
    def defense(self):
        print(f"{self._name} tenta realizar uma defesa!")
        return random.randint(1, self._resistance)-1
    
    def rest(self):
        print(f"{self._name} descansa para recuperar vida.")
        bonus=random.randint(1,10)+20
        print(f"+{bonus} pontos de vida.")
        self.hp+=bonus
        return
    
    def getstrength(self):
        return self._strength
    
    def getresistance(self):
        return self._resistance
    
    def getname(self):
    	return self._name
    
    def show_status(self):
        print(f"-----{self._name}-----")
        print(f"Vida atual: {self.hp}")
        print(f"Resistência: {self._resistance}")
        print(f"Força: {self._resistance}")
        print("----------------------")

class Enemy:
    def __init__(self,name):
        self._name=name
        self.hp=random.randint(1,10)+70
        self._resistance=int(self.hp/10)
        self._strength=self._resistance

    def attack(self):
        print(f"{self._name} tenta realizar um ataque!")
        return random.randint(1, self._strength)+self._strength
    
    def defense(self):
        print(f"{self._name} tenta realizar uma defesa!")
        return random.randint(1, self._resistance)-1
    
    def getname(self):
    	return self._name
    
    def getstrength(self):
        return self._strength
    
    def getresistance(self):
        return self._resistance
    
def Battle(p, e):
    os.system('cls')
    print(f"Batalha de {p.getname()} contra {e.getname()}!")
    while p.hp>0 and e.hp>0:
        print("Escolha uma ação:")
        print("1 para atacar")
        print("2 para defender")
        print("3 para descansar")
        opc=int(input())
        if opc==1:
            atk_p=p.attack()
            dfs_p=p.getresistance()
        elif opc==2:
            atk_p=0
            dfs_p=p.getresistance()+p.defense()
        elif opc==3:
            atk_p=0
            dfs_p=p.getresistance()
            p.rest()
        else:
            print("Você se confunde no seu turno e não faz nada.")

        act=random.randint(1,4)
        if act>=1 and act<=3:
            atk_e=e.attack()
            dfs_e=e.getresistance()
        else:
            atk_e=0
            dfs_e=e.getstrength()

        if atk_p>dfs_e:
            print("Você acerta um ataque!")
            e.hp-=random.randint(1,p.getstrength())
        else:
            print("Você erra o seu ataque!")

        if atk_e>dfs_p:
            print("O oponente acerta um ataque!")
            p.hp-=random.randint(1,e.getstrength())
        elif atk_e>0 and atk_p==0:
            print("Você se defende!")
        else:
            print("O oponente erra o ataque!")

        print(f"Sua vida atual: {p.hp}")
        print(f"Vida atual do oponente: {e.hp}")
        a=input("Pressione enter para prosseguir")
        os.system('cls')
    if p.hp<=0:
        return e.getname()
    else:
        return p.getname()
    
print("Mini RPG em python!")
nome=input("Selecione seu nome para começar: ")
jogador=Player(nome)
opc='0'
while opc!='3':
    print("Selecione sua opção:")
    print("1 para lutar")
    print("2 para ver personagem")
    print("3 para sair")
    opc=input()
    if opc=='1':
        vencedor=Battle(jogador,Enemy(random.choice(name_list)))
        if vencedor!=jogador.getname():
            print("Você perdeu! Restaurando personagem...")
            jogador.hp=100
        else:
            print("Meus parabéns! Você venceu!")
    elif opc=='2':
        jogador.show_status()
    elif opc=='3':
        break
    else:
        print("Essa opção não existe!")
    a=input("Pressione enter para prosseguir")
    os.system("cls")
    
print("Obrigado por jogar!")