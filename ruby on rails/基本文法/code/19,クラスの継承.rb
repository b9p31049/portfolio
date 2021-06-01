# クラスの継承
# 異なるクラスで同じクラスが必要な場合

class Greeting
    def hello
        puts "こんにちは！#{@name}さん"
    end
end

class User < Greeting
    def initialize(name)
        @name = name
    end

    # オーバーライドしている
    def hello
        super
        puts "Hello, #{@name}"
    end
end

user1 = User.new('Sato')
user1.hello

user2 = User.new('Tanakaa')
user2.hello


# メソッドの上書き(オーバーライド)
# 継承するメソッド名を同じにする

# super を付けることで親クラスの呼び出し可能