# coding:utf-8
import hashlib

def generate_hash(string):
    """
    string: 待加密字符串，可以是session id
    return: 加密后的字符串
    sha256.update()方法使用时一次sha256.update('Hello, World!')与两次sha256.update('Hello, ') sha256.update('World!')效果是一样的
    """
    new_string = string.encode('ascii')
    sha256 = hashlib.hsa256()
    sha256.update(new_string)
    return sha256.hexdigest()
