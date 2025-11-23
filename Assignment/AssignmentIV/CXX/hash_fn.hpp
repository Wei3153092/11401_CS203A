#include <cstdlib>      // for std::llabs
#include <iostream>     // for std::cerr

namespace HashUtils {

    // 實作整數鍵雜湊函數：乘法法 (Multiplication Method)
    // 參考 Knuth 的黃金比例常數 (Golden Ratio constant) 0x9E3779B9
    unsigned int hashIntDivision(int key, unsigned int m) {
        if (m == 0) {
            std::cerr << "錯誤: 雜湊表大小 m 必須大於 0。\n";
            return 0;
        }
        
        // 處理負數鍵：取絕對值
        long long positiveKey = std::llabs((long long)key);
        
        // 使用黃金比例常數 (0x9E3779B9) 進行乘法雜湊
        // 這是對於 32 位元整數而言，具有良好隨機性的乘數。
        const unsigned int A = 2654435769U; 
        
        // 乘法法核心計算：h(k) = (k * A) >> (32 - s)
        // 由於我們最終仍然要模 m，可以簡化為 (k * A) % m，但使用乘法常數的目的是確保高位位元的分佈均勻性。
        // 對於 M=1024 (2^10) 這樣的 M，乘法法的效果最好。這裡為保持簡單，我們仍然使用模運算來適應所有 M。
        unsigned int hashValue = static_cast<unsigned int>(positiveKey) * A;
        
        return hashValue % m;
    }

    // 實作字串鍵雜湊函數：djb2 演算法
    // 這是一種非常流行的字串雜湊函數，通常用於 Linux 核心。
    unsigned int hashStringPolynomial(const std::string& key, unsigned int m) {
        if (m == 0) {
            std::cerr << "錯誤: 雜湊表大小 m 必須大於 0。\n";
            return 0;
        }

        // djb2 演算法的初始值
        unsigned int hashValue = 5381; 
        
        // djb2 演算法的核心循環：hash = hash * 33 + c
        for (char c : key) {
            // hash = hash * 33 + c
            // 由於 (hash << 5) 是 hash * 32，因此 (hash << 5) + hash 相當於 hash * 33
            hashValue = ((hashValue << 5) + hashValue) + static_cast<unsigned int>(c);
        }

        // 最後一步：模 m
        return hashValue % m;
    }

} // namespace HashUtils