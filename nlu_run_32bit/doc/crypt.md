# 数据加密 组件库 crypt.dll 使用说明

Z语言接口使用说明



## 1.数据处理

##### 1.1：hex转字符串

| 接口 | bts  | hex转字符串（长度扩展两倍） |
| ---- | ---- | --------------------------- |
| 入参 | buf  | 需要扩展的数据串            |
| 反回 | str  | 返回两倍长的字符串          |

```c
str bts(buf) 
/* demo 
bts("\xA1\xB2\xc3") 返回 str[6]"A1B2C3"
bts'A1B2c3' 返回 str[6]"A1B2C3"
*/
```



##### 1.2：字符串转hex

| 接口 | stb  | hex转字符串（长度为源数据的一半）                         |
| ---- | ---- | --------------------------------------------------------- |
| 入参 | str  | 需要转换的字符串（输入参数必须在 0~9,A~F,a~f,之间才有效） |
| 反回 | buf  | 返回半倍长的数据串                                        |

```c
buf stb(str) 
/* demo 
stb("A1B2C3") 返回 buf[3]' A1 B2 C3'
stb"303132" 返回 buf[3]' 30 31 32' (与 str[3]"012" 数据相同)
*/
```



##### 1.3：base64编码

| 接口 | b64e | base64编码（长度为源数据的4/3） |
| ---- | ---- | ------------------------------- |
| 入参 | buf  | 需要转换的数据串                |
| 反回 | str  | 返回4/3长度的字符串             |

```c
str b64e(buf) 
/* demo 
b64e('11 22 33') 返回 str[4]"ESIz"
*/
```



##### 1.4：base64解码

| 接口 | b64d | base64解码（长度为源数据的3/4） |
| ---- | ---- | ------------------------------- |
| 入参 | str  | 需要转换的字符串                |
| 反回 | buf  | 返回半倍长的数据串              |

```c
buf b64d(str) 
/* demo 
b64d("ESIz") 返回：buf[3]'11 22 33 '
*/
```



##### 1.5： 随机数

| 接口 | rand     | 随机数生成接口                              |
| ---- | -------- | ------------------------------------------- |
| 入参 | len/null | 输出随机数长度，为空直接输出随机数          |
| 反回 | bool     | 指定长度的随机数，没有入参时返回int型随机数 |

```c
buf/num settts(len/null) 
/* demo 
rand() 返回 int:-266015095
rand(16) 返回 buf[16]' 94 E4 07 EE 87 58 0F D8 16 60 6B 39 77 71 97 A2'
*/
```




## 2.摘要算法

##### 2.1： 哈希算法

| 接口 | md   | 哈希算法                                        |
| ---- | ---- | ----------------------------------------------- |
| 入参 | flag | 算法标识(目前开放了“md5”,"sha1","sha256","sm3") |
| 入参 | data | 输入数据(buf/str)                               |
| 反回 | buf  | 成功返回摘要值，失败返回 false                  |

```c
buf md(flag,data) 
/* demo 
md("md5","abcdef123456789") 返回：buf[16]'CA 69 66 E8 47 9D 72 DF 7C BD DB 45 84 69 74 95 '
md("sha1","abcdef123456789") 返回: buf[20]' 7B 34 D8 0D B0 4D 99 A9 6F 11 57 F9 0C 2F 5B A3 E3 8F 3A BA'
md("sha256","abcdef123456789") 返回: buf[32]' A8 88 E3 C6 DE 1F 90 D1 2F 88 99 52 C0 C7 D0 AC 23 0E 90 14 18 99 14 F6 5C 54 8B 8A 3B 44 EF 45'
md("sm3","abcdef123456789") 返回: buf[32]' 45 40 60 F0 D4 15 6B F3 5D DA 03 F7 F2 E1 65 E6 84 F0 33 79 94 C9 DC 74 AC 53 D0 C9 49 56 00 BF'
*/
```



##### 2.2： 哈希MAC算法

| 接口 | mdc  | 哈希MAC算法                                     |
| ---- | ---- | ----------------------------------------------- |
| 入参 | flag | 算法标识(目前开放了“md5”,"sha1","sha256","sm3") |
| 入参 | key  | 密钥                                            |
| 入参 | data | 输入数据(buf/str)                               |
| 反回 | buf  | 成功返回摘要值，失败返回 false                  |

```c
buf mdc(flag,key,data) 
/* demo 
mdc("sha1","123456","abcdef123456789") 返回：buf[20]'F4 2C 8E A1 A4 DF AF 2E 21 AA D3 EE 44 54 2B F8 C8 30 31 2E '
*/
```



## 3.对称加密算法

##### 3.1： ECB加密算法

| 接口 | ecbe | ECB加密算法                           |
| ---- | ---- | ------------------------------------- |
| 入参 | flag | 算法标识(目前开放了“des”,"aes","sm4") |
| 入参 | key  | 密钥（由长度决定多倍算法）            |
| 入参 | data | 输入数据(buf/str)                     |
| 反回 | buf  | 成功返回摘要值，失败返回 false        |

```c
buf ecbe(flag,key,data) 
/* demo 
ecbe("des",'1122334455667788',"12345678") 返回：buf[8]'33 79 0D E1 BF FF 1E 2B '
ecbe("des",'11111111111111112222222222222222',"12345678") 返回：buf[8]' A9 03 47 0E D2 0C 5D D4'
ecbe("aes",'11111111111111112222222222222222',"12345678abcdefgh") 返回：buf[16]' 03 B0 E0 74 D1 69 1D C2 DE 77 C6 EF 52 0C CA BA'
ecbe("sm4",'11111111111111112222222222222222',"12345678abcdefgh") 返回：buf[16]' 42 87 6A CE 20 C8 34 5A BD 51 7D 2A DE CA D7 E0'
*/
```



##### 3.2： ECB解密算法

| 接口 | ecbd | ECB解密算法                           |
| ---- | ---- | ------------------------------------- |
| 入参 | flag | 算法标识(目前开放了“des”,"aes","sm4") |
| 入参 | key  | 密钥（由长度决定多倍算法）            |
| 入参 | data | 输入数据(buf/str)                     |
| 反回 | buf  | 成功返回摘要值，失败返回 false        |

```c
buf ecbd(flag,key,data) 
/* demo 
ecbd("aes",'11223344556677881122334455667788',"1234567812345678") 返回：buf[16]'17 DC C9 6E D5 01 B6 6F D6 41 4D EC 5D 64 71 5D '
*/
```



##### 3.3： CBC加密算法

| 接口     | cbce    | ECB加密算法                           |
| -------- | ------- | ------------------------------------- |
| 入参     | flag    | 算法标识(目前开放了“des”,"aes","sm4") |
| 入参     | key     | 密钥（由长度决定多倍算法）            |
| 入参     | data    | 输入数据(buf/str)                     |
| 初始向量 | iv/null | 当缺失时默认全0x00                    |
| 反回     | buf     | 成功返回摘要值，失败返回 false        |

```c
buf cbce(flag,key,data,iv/null) 
/* demo 
cbce("sm4",'11223344556677881122334455667788',"1234567812345678")返回：buf[16]'ED 19 07 E2 16 DA DD 92 79 F1 3D 17 0F 1C CD 28 '
cbce("sm4",'11223344556677881122334455667788',"1234567812345678","1234567812345678")返回：buf[16]' F4 D1 61 28 79 0F A2 C9 B1 53 7F E0 67 32 18 EC'
*/
```



##### 3.4： CBC解密算法

| 接口     | cbcd    | CBC解密算法                           |
| -------- | ------- | ------------------------------------- |
| 入参     | flag    | 算法标识(目前开放了“des”,"aes","sm4") |
| 入参     | key     | 密钥（由长度决定多倍算法）            |
| 入参     | data    | 输入数据(buf/str)                     |
| 初始向量 | iv/null | 当缺失时默认全0x00                    |
| 反回     | buf     | 成功返回摘要值，失败返回 false        |

```c
buf cbcd(flag,key,data,iv/null) 
/* demo 
cbcd("aes",'11223344556677881122334455667788',"1234567812345678","00998877665544332211998877665544") 返回：buf[16]'27 EC F0 57 ED 39 81 58 E0 77 78 D9 69 50 42 6E ' 
*/
```

## 4.非对称算法

##### 4.1： 生成密钥对

| 接口 | pk_get | 密钥对生成                                                   |
| ---- | ------ | ------------------------------------------------------------ |
| 入参 | key/"" | 密钥数据（密钥数据/为“”时返回 pem 格式密钥，当"bin"时返回sm2:x[32]+y[32]+d[32],<br />rsa: n[l]+e[3]+d[l]+p[l/2]+q[l/2]+dp[l/2]+dq[l/2]+qp[l/2]  ） |
| 入参 | flag   | 标识(目前开放了"sm2"/"rsa:1024"/"rsa:2048")                  |
| 反回 | ctx    | 成功返回密钥类，失败返回 false                               |

```c
ctx pk_get(key,flag) 
/* demo 
生成rsa:1024 密钥对：ctr=pk_get("","rsa:2048") 
生成SM2国密密钥对：ctm=pk_get("","sm2")
*/
```



##### 4.1： 导入密钥对

| 接口 | pk_inkey | 导入密钥对                         |
| ---- | -------- | ---------------------------------- |
| 入参 | key      | pem 格式或 cer格式，公钥私钥都支持 |
| 反回 | ctx      | 成功返回密钥类，失败返回错误码     |

```c
ctx pk_inkey(key) 
/* demo 
ctx=pk_inkey("-----BEGIN PUBLIC KEY-----MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQDRipxET5w3cX7QJer9NlbHC7PwHOQsQW1EIfoqueFhyInTehd+HPbmAZAYZV/x9oESk7oGg5orJOhxd01k5jNGaQYB2N+OlqnhIDFZzfdpcdT5KUs+kTRe4QGrnu0qwQe07xT5ZbQlnr1oBIQTbGz4bUjJnXVgdqHJ/Ht/IWDZsQIDAQAB-----END PUBLIC KEY-----");

---<out ctx
[ctx]any:0298EB0C
true
*/
```



##### 4.3： 释放密钥类

| 接口 | pk_free | 释放由 pk_inkey 或 pk_get 返回密钥类      |
| ---- | ------- | ----------------------------------------- |
| 入参 | ctx_key | 由于ctx占有一定空间，所以用完之后需要释放 |
| 反回 | bool    | 成功返回true，失败返回 false              |

```c
bool pk_free(ctx) 
/* demo 
ctx=pk_inkey("....");
......
pk_free(ctx);
*/
```



##### 4.4： 导出公钥

| 接口 | pk_outpub | 从密钥类中导出公钥                        |
| ---- | --------- | ----------------------------------------- |
| 入参 | ctx_key   | 密钥类（由 pk_inkey 或 pk_get 返回）      |
| 反回 | keybuf    | 成功返回公钥buf(ASN1标准)，失败返回 false |

```c
buf pk_outpub(ctx) 
/* demo 
pk_outpub(ctx)
buf[162]' 30 81 9F 30 0D 06 09 2A 86 48 86 F7 0D 01 01 01 05 00 03 81 8D 00 30 81 89 02 81 81 00 D1 8A 9C 44 4F 9C 37 71 7E D0 25 EA FD 36 56 C7 0B B3 F0 1C E4 2C 41 6D 44 21 FA 2A B9 E1 61 C8 89 D3 7A 17 7E 1C F6 E6 01 90 18 65 5F F1 F6 81 12 93 BA 06 83 9A 2B 24 E8 71 77 4D 64 E6 33 46 69 06 01 D8 DF 8E 96 A9 E1 20 31 59 CD F7 69 71 D4 F9 29 4B 3E 91 34 5E E1 01 AB 9E ED 2A C1 07 B4 EF 14 F9 65 B4 25 9E BD 68 04 84 13 6C 6C F8 6D 48 C9 9D 75 60 76 A1 C9 FC 7B 7F 21 60 D9 B1 02 03 01 00 01'
*/
```



##### 4.5： 导出私钥

| 接口 | pk_outpri | 从密钥类中导出私钥                        |
| ---- | --------- | ----------------------------------------- |
| 入参 | ctx_key   | 密钥类（由 pk_inkey 或 pk_get 返回）      |
| 反回 | keybuf    | 成功返回私钥buf(ASN1标准)，失败返回 false |

```c
buf pk_outpub(ctx) 
/* demo 
pk_outpri(ctx)
int:-16512 //如ctx中不存在私钥
*/
```



##### 4.6： 公钥加密

| 接口 | pk_enc   | 公钥加密                             |
| ---- | -------- | ------------------------------------ |
| 入参 | key      | 密钥类（由 pk_inkey 或 pk_get 返回） |
| 入参 | data     | 需要加密的数据                       |
| 入参 | padding  | 填充类型（如“v15”,"v21"(pass)        |
| 反回 | enc data | 成功返回被加密数据，失败返回错误码   |

```c
buf pk_enc(key,data,padding/null) 
/* demo 
pk_enc(ctx,"12345678","v21")
返回：buf[128]' 12 E8 C5 03 0F 9F A2 BC 02 D7 E8 E5 D4 A4 81 A8 CC 37 CE E7 51 F5 D9 66 88 1A 8A 41 2B D9 B9 C2 1E 6E 1B A5 F6 D6 DE DE 32 54 A0 90 DE DF 9E 31 7B 0E EA D3 E1 A4 E3 29 BC BE 98 BC 52 CD 11 6F 25 E6 63 EC 05 04 61 A2 A0 5E 10 79 BD D1 7F B8 47 4A F9 C9 4E 2A 2A 33 2E BE 59 16 EC 49 06 60 00 A3 FA 64 B0 05 AA F7 F5 F5 2D 99 FC 67 14 60 F6 8B 47 FC 3A F9 05 1E E5 B3 BA C3 67 FD BF 47'
*/
```



##### 4.7： 私钥解密

| 接口 | pk_dec   | 私钥解密                             |
| ---- | -------- | ------------------------------------ |
| 入参 | key      | 密钥类（由 pk_inkey 或 pk_get 返回） |
| 入参 | data     | 需要解密的数据                       |
| 入参 | padding  | 填充类型（如“v15”,"v21"(pass)        |
| 反回 | dec data | 成功返回被加密数据，失败返回错误码   |

```c
buf pk_dec(key,data,padding/null) 
/* demo 
pk_dec(ctx,' 12 E8 C5 03 0F 9F A2 BC 02 D7 E8 E5 D4 A4 81 A8 CC 37 CE E7 51 F5 D9 66 88 1A 8A 41 2B D9 B9 C2 1E 6E 1B A5 F6 D6 DE DE 32 54 A0 90 DE DF 9E 31 7B 0E EA D3 E1 A4 E3 29 BC BE 98 BC 52 CD 11 6F 25 E6 63 EC 05 04 61 A2 A0 5E 10 79 BD D1 7F B8 47 4A F9 C9 4E 2A 2A 33 2E BE 59 16 EC 49 06 60 00 A3 FA 64 B0 05 AA F7 F5 F5 2D 99 FC 67 14 60 F6 8B 47 FC 3A F9 05 1E E5 B3 BA C3 67 FD BF 47',"v21")
返回：buf[8]' 31 32 33 34 35 36 37 38'
*/
```



##### 4.8： 私钥签名

| 接口 | pk_sign         | 私钥签名                             |
| ---- | --------------- | ------------------------------------ |
| 入参 | key             | 密钥类（由 pk_inkey 或 pk_get 返回） |
| 入参 | data            | 需要解密的数据                       |
| 入参 | hash_id&padding | 填充类型（如“sha1v15”,"sha256v21")   |
| 反回 | dec data        | 成功返回被加密数据，失败返回错误码   |

```c
buf pk_sign(key,data,hash_id&padding/no) 
/* demo 
pk_sign(ctx,"123456789","sha1v15")
返回：buf[128]' A3 14 E2 E9 59 EC 2D 79 D6 83 70 2F 3F 5E 8A 3F 84 90 15 B7 C8 65 B4 AC FF F7 20 23 88 AF CB FE B2 AF 3A 43 32 94 11 39 FE 09 AB FB C6 6A 86 87 07 F9 64 51 BB 56 8B F8 E6 A4 6D 24 B1 6F F0 F8 06 43 E6 ED BA DC EE 45 3E F6 20 53 E8 75 FC BC 5D DE A4 87 7F 65 E4 34 E9 4A 48 FE 7A 96 18 DD 15 9B A6 34 16 92 94 91 BF FE 00 5A 06 0B B7 DF F2 CF 70 3A 03 58 A4 7C D6 98 51 A0 CD 62 87 AA'
*/
```



##### 4.9： 公钥验证签名

| 接口 | pk_verify       | 公钥验证签名                         |
| ---- | --------------- | ------------------------------------ |
| 入参 | key             | 密钥类（由 pk_inkey 或 pk_get 返回） |
| 入参 | data            | 需要验证的数据                       |
| 入参 | sign            | 签名结果数据                         |
| 入参 | hash_id&padding | 填充类型（如“sha1v15”,"sha256v21")   |
| 反回 | bool            | 成功返回true，失败返回false          |

```c
bool pk_verify(key,data,sign,hash_id&padding) 
/* demo 
pk_verify(ctx,"123456789",' A3 14 E2 E9 59 EC 2D 79 D6 83 70 2F 3F 5E 8A 3F 84 90 15 B7 C8 65 B4 AC FF F7 20 23 88 AF CB FE B2 AF 3A 43 32 94 11 39 FE 09 AB FB C6 6A 86 87 07 F9 64 51 BB 56 8B F8 E6 A4 6D 24 B1 6F F0 F8 06 43 E6 ED BA DC EE 45 3E F6 20 53 E8 75 FC BC 5D DE A4 87 7F 65 E4 34 E9 4A 48 FE 7A 96 18 DD 15 9B A6 34 16 92 94 91 BF FE 00 5A 06 0B B7 DF F2 CF 70 3A 03 58 A4 7C D6 98 51 A0 CD 62 87 AA',"sha1v15")
返回：true
*/
```



##### 4.10： RSA公钥运算

| 接口 | pk_rsapub | RSA公钥运算                                                  |
| ---- | --------- | ------------------------------------------------------------ |
| 入参 | key       | 密钥类（由 pk_inkey 或 pk_get 返回）                         |
| 入参 | data      | 需要验证的数据                                               |
| 反回 | bool      | 成功返回运算后的数据，失败返回错误码(数据长度不匹配返回false） |

```c
buf pk_rsapub(key,data) 
/* demo 

*/
```

##### 4.11： RSA私钥运算

| 接口 | pk_rsapri | RSA私钥运算                                                  |
| ---- | --------- | ------------------------------------------------------------ |
| 入参 | key       | 密钥类（由 pk_inkey 或 pk_get 返回）                         |
| 入参 | data      | 需要验证的数据                                               |
| 反回 | bool      | 成功返回运算后的数据，失败返回错误码(数据长度不匹配返回false） |

```c
buf pk_rsapri(key,data) 
/* demo 

*/
```



## 5.证书

##### 5.1： 合成证书请求

| 接口 | gp10           | 合成PKCS#10请求证书                                    |
| ---- | -------------- | ------------------------------------------------------ |
| 入参 | key            | 密钥类（由 pk_inkey 或 pk_get 返回）                   |
| 入参 | subname        | 请求者信息                                             |
| 入参 | shabitlen/null | 哈希强度（当密钥为sm2时，不需要此参数，默认为256强度） |
| 反回 | bool           | 成功返回pem，失败返回false                             |

```c
bool gp10(key,subname,shabitlen) 
/* demo 
gp10(ctx,"CN=China.UnionPay",256)
返回：str[542]"-----BEGIN CERTIFICATE REQUEST-----
MIIBWDCBwgIBADAZMRcwFQYDVQQDDA5DaGluYS5VbmlvblBheTCBnzANBgkqhkiG
9w0BAQEFAAOBjQAwgYkCgYEA3tsu3KAY5zMLw8pdrFx7TejqdOqlcwnd0rareYfw
AmYecl4zQ9VdZPsMCRoRssG+Lmrc0dDm7Vj8GnUNdCyqE8vY/xWWodSf1g5hp43L
f6Kb2MXFCW2GQeLK0neY28x5UfS2qtYi85buigrVnfJTNIuGLDz/Q8OelO5TvDE3
pQsCAwEAAaAAMA0GCSqGSIb3DQEBCwUAA4GBAEBoiT39aDdwywICrEwguJzwmjIl
/dXXCowYiEHuQ2U7RgjpAY879wzMlKjf81n5fjkOYtMQuNEc1MamicyjmhkHMl02
sloT9fHSbaRYuCrGcC7yYY/inbTg673i3uh9GwXXFHMMYvsLCelfjZEZAKugR6mE
i6bR6bUgUZxpE57i
-----END CERTIFICATE REQUEST-----
"
*/
```



##### 5.2： 证书验证

| 接口 | x509v   | 验证证书                    |
| ---- | ------- | --------------------------- |
| 入参 | cer     | 需要验证的证书              |
| 入参 | cerlast | 上一级证书                  |
| 反回 | bool    | 成功返回ture，失败返回false |

```c
bool x509v(cernext,cerlast) 
```



##### 5.3： 颁发证书

| 接口 | x509cw | 授权发放证书                |
| ---- | ------ | --------------------------- |
| 入参 | sn     | 证书SN号                    |
| 入参 | md     | 证书签名算法标识            |
| 入参 | p10    | 请求证书                    |
| 入参 | isskey | 发布者私钥                  |
| 入参 | rootca | 上一级证书                  |
| 反回 | bool   | 成功返回ture，失败返回false |

```c
str x509cw(sn,md,p10,issname,rootca) 
```



##### C 程序引用方法定义基础代码：**[自然语言理解NLU-第三方功能接入](https://gitee.com/kebo521/nlu3)**