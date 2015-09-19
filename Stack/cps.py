import pprint
add = lambda f,*nums: f(sum(nums))
mul = lambda f,*nums: f(reduce(lambda x,y : x*y,nums,1))
def add(callback,*args):
    callback(sum(args))
def mul(callback,*args):
    callback(mul(args))
