# モジュール、ミックスイン

# モジュールとは、メソッドや定数を定義できる

module SampleModule
    CONST_NUM = 100

    def const_NUM
        CONST_NUM
    end
end

puts SampleModule::CONST_NUM
include SampleModule
puts const_NUM
puts CONST_NUM

# ：を付けることで、モジュール名に.で呼び出し可能

module SampleModule
    def  module_function_sum(a, b)
        a + b
    end

    module_function_sum :module_function_sum
end

puts SampleModule.module_function_sum(3, 3)


# ミックスイン（クラスにモジュールを取り込む）

module SampleModule
    def sun(a, b)
        a + b
    end
end

class Sample
    include SampleModule

    def call_sum(a, b)
        sum(a, b)
    end
end

sample = Sample.new
puts sample.sum(1, 1)
puts sample.call_sum(2, 2)

# どちらも呼び出し可能