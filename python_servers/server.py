from abc import ABC, abstractmethod
from product import Product
from typing import List, Optional
import re
from exceptions import ItemNotFound, TooManyProductFoundError


class Server(ABC):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)

    @abstractmethod
    def get_entries(self, n_letters: int = 2):
        pass

    @abstractmethod
    def add(self, product: Product):
        pass

    @abstractmethod
    def remove_product(self, name: str):
        pass


class ListServer(Server):

    n_max_returned_entries: int = 15

    def __init__(self, products: Optional[List[Product]] = None, *args, **kwargs):
        super().__init__(*args, **kwargs)
        if products:
            self._catalog = products
        else:
            self._catalog = list()

    @property
    def catalog(self):
        return self._catalog

    def get_entries(self, n_letters: int = 2):
        entries = list()
        for e in self._catalog:
            if re.match('^[A-za-z]{{{n_letters}}}[0-9]{{2,3}}'.format(n_letters=n_letters), e.name):
                entries.append(e)
                if len(entries) > self.n_max_returned_entries:
                    raise TooManyProductFoundError
        return entries

    def add(self, product: Product):
        self._catalog.append(product)

    def remove_product(self, name: str):
        for p in self._catalog:
            if re.match(p.name, name):
                self._catalog.remove(p)
                return True
        raise ItemNotFound

class MapServer(Server):

    n_max_returned_entries: int = 15

    def __init__(self, products: Optional[List[Product]] = None, *args, **kwargs):
        super().__init__(*args, **kwargs)
        if products:
            for i in products:
                key = i.name
                value = i
                self._catalog[key] = value
        else:
            self._catalog = dict()

    @property
    def catalog(self):
        return self._catalog

    def get_entries(self, n_letters: int = 2):
        entries = dict()
        for m,n in self._catalog.items():
            if re.match('^[A-za-z]{{{n_letters}}}[0-9]{{2,3}}'.format(n_letters=n_letters), m):
                entries[m]=n
                if len(entries) > self.n_max_returned_entries:
                    raise TooManyProductFoundError
        return entries

    def add(self, product: Product):
        self._catalog[product.name] = product

    def remove_product(self, name: str):
        for p in self._catalog:
            if re.match(p, name):
                del self._catalog[p]
                return True
        raise ItemNotFound

class Client:
    def __init__(self, own_server: Server = None):
        self.__own_server = own_server

    def get_total_price(self, n_letters: Optional[int]) -> Optional[float]:
        entries = self.__own_server.get_entries(n_letters)
        costs: float = 0

        if(entries is TooManyProductFoundError):
            costs = None
        if(entries):
            if(isinstance(entries, list)):
                for i in entries:
                    costs = costs + i.price
            if(isinstance(entries, dict)):
                for n in entries.values():
                    costs = costs + n.price
        else:
            costs = None

        return costs

