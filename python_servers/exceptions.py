class ServerError(Exception):
    pass


class TooManyProductFoundError(ServerError):
    pass


class ProductError(Exception):
    pass


class ClientError(Exception):
    pass


class InvalidIDError(ProductError):
    pass


class ItemNotFound(ProductError):
    pass
