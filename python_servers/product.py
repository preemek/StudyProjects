import re
from exceptions import InvalidIDError


def is_valid_name(name: str) -> bool:
    if re.match('^[A-za-z]+[0-9]+$', name):
        return True
    else:
        return False


class Product:
    def __init__(self, name: str, price: float):
        if is_valid_name(name):
            self._name = name
        else:
            raise InvalidIDError
        self._price = price

    @property
    def name(self):
        return self._name

    @name.setter
    def name(self, name):
        if is_valid_name(name):
            self._name = name
        else:
            raise InvalidIDError

    @property
    def price(self):
        return self._price

    @price.setter
    def price(self, price):
        self._price = price
