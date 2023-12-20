from abc import ABC, abstractmethod

class animal(ABC):
    def __init__(self, name:str, properties:dict, **kwargs):
        self.name = name
        [setattr(self, i, properties[i]) for i in properties if i not in self.__dict__]
        [setattr(self, i, kwargs[i]) for i in kwargs if i not in self.__dict__]

    def __str__(self) -> str:
        print(r"this is an animal of species {self.species} its name is {self.name}") \
                if hasattr(self, species) else \
                print(r"The name is {self.name}")

    def get_properties(self) -> dict:
        self_dir = dir(self)
        dict = {i : self.__dict__[i] for i in self.__dict__}
        dict.update({i : getattr(self, i) for i in self_dir if i[0] != '_'})
        return dict

class dog (animal):
    species:str    = "Canine"
    limbs: int      = 4

class cat (animal):
    species:str    = "Felis"
    limbs: int      = 4

class worm (animal):
    species:str   = "necrophilia"
    limbs:int      = 0

if __name__ == "__main__":
    properties = { 'petname':"james", 'age':14, 'likes': ["baseball", "babies", "scratching"], 'name': "Jeffery" }
    myDog = dog("Henry", properties, god="Ikechukwu")
    print(myDog.get_properties())
