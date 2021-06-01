# メソッドの定義

# 最も基本的なもの
def hello
    puts "hello!"
end

hello


# 引数があるメソッド

def hello(name)
    puts "Hello, #{name}. "
end

hello('kozima')

#　引数デフォルト値

def hello(name = 'unknow')
    puts "Hello #{name}"
end

hello


# 引数のラベル

def hello(name: 'Unknow')
    puts "Hello, #{name}"
end


# 可変超引数

# sum・・・全てをたす
# *valuse ・・・　複数の引数を渡された場合、arrayメソッドで返し、valuesの変数に格納される
# inject ・・・ arrayに備わっている、合計を計算
def sum(*valuse)
    valuse.inject { |total, n| total + n }
end

puts sum(1, 2,  3, 4)

#　ハッシュの形式で渡す
def some_method(**kv_values)
    puts kv_values
end

some_method(param1: :aaa, param2: :bbb)


# 必須の仮引数　→　オプションの仮引数　→　オプションの仮引数

