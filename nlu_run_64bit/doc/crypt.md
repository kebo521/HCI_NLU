------

# Data Encryption Component Library crypt.dll Usage Guide

Z-Language Interface Specification

------

## 1. Data Processing

##### 1.1: Hex to String

| Interface | `bts` | Converts hex to ASCII string (doubles length) |
| --------- | ----- | --------------------------------------------- |
| Parameter | `buf` | Binary data buffer                            |
| Returns   | `str` | ASCII string (double original length)         |

```
str bts(buf)  
/* Example:  
bts("\xA1\xB2\xC3") returns "A1B2C3"  
bts'A1B2c3' returns "A1B2C3"  
*/  
```

##### 1.2: String to Hex

| Interface | `stb` | Converts ASCII string to hex (halves length) |
| --------- | ----- | -------------------------------------------- |
| Parameter | `str` | ASCII string (valid chars: 0-9, A-F, a-f)    |
| Returns   | `buf` | Binary data buffer                           |

```
buf stb(str)  
/* Example:  
stb("A1B2C3") returns '\xA1\xB2\xC3'  
stb"303132" returns '\x30\x31\x32' (equals "012")  
*/  
```

##### 1.3: Base64 Encode

| Interface | `b64e` | Base64 encoding (4/3 output length) |
| --------- | ------ | ----------------------------------- |
| Parameter | `buf`  | Binary data buffer                  |
| Returns   | `str`  | Base64-encoded string               |

```
str b64e(buf)  
/* Example:  
b64e('\x11\x22\x33') returns "ESIz"  
*/  
```

##### 1.4: Base64 Decode

| Interface | `b64d` | Base64 decoding (3/4 output length) |
| --------- | ------ | ----------------------------------- |
| Parameter | `str`  | Base64-encoded string               |
| Returns   | `buf`  | Binary data buffer                  |

```
buf b64d(str)  
/* Example:  
b64d("ESIz") returns '\x11\x22\x33'  
*/  
```

##### 1.5: Random Number Generator

| Interface | `rand` | Generates cryptographically secure random data |
| --------- | ------ | ---------------------------------------------- |
| Parameter | `len`  | Output length (optional)                       |
| Returns   | Mixed  | Random number (no param) or random buffer      |

```
mixed rand(len)  
/* Example:  
rand() returns integer: -266015095  
rand(16) returns 16-byte buffer  
*/  
```

------

## 2. Digest Algorithms

##### 2.1: Hash Algorithm

| Interface  | `md`           | Computes message digest                                      |
| ---------- | -------------- | ------------------------------------------------------------ |
| Parameters | `flag`  `data` | Algorithm ID ("md5", "sha1", "sha256", "sm3")  Input data (buffer/string) |
| Returns    | `buf`          | Digest value (false on error)                                |

```
buf md(flag, data)  
/* Example:  
md("md5", "abcdef123456789") returns 16-byte digest  
*/  
```

##### 2.2: HMAC Algorithm

| Interface  | `mdc`                 | Computes keyed-hash MAC              |
| ---------- | --------------------- | ------------------------------------ |
| Parameters | `flag`  `key`  `data` | Algorithm ID  Secret key  Input data |
| Returns    | `buf`                 | MAC value (false on error)           |

```
buf mdc(flag, key, data)  
```

------

## 3. Symmetric Encryption

##### 3.1: ECB Encryption

| Interface  | `ecbe`                | ECB mode encryption                                   |
| ---------- | --------------------- | ----------------------------------------------------- |
| Parameters | `flag`  `key`  `data` | Algorithm ("des","aes","sm4")  Secret key  Input data |
| Returns    | `buf`                 | Ciphertext (false on error)                           |

```
buf ecbe(flag, key, data)  
```

##### 3.2: ECB Decryption

| Interface  | `ecbd`                | ECB mode decryption                  |
| ---------- | --------------------- | ------------------------------------ |
| Parameters | `flag`  `key`  `data` | Algorithm ID  Secret key  Ciphertext |
| Returns    | `buf`                 | Plaintext (false on error)           |

```
buf ecbd(flag, key, data)  
```

##### 3.3: CBC Encryption

| Interface  | `cbce`                      | CBC mode encryption                                      |
| ---------- | --------------------------- | -------------------------------------------------------- |
| Parameters | `flag`  `key`  `data`  `iv` | Algorithm ID  Secret key  Input data  IV (default: NULL) |
| Returns    | `buf`                       | Ciphertext (false on error)                              |

```
buf cbce(flag, key, data, iv)  
```

##### 3.4: CBC Decryption

| Interface  | `cbcd`                      | CBC mode decryption                                      |
| ---------- | --------------------------- | -------------------------------------------------------- |
| Parameters | `flag`  `key`  `data`  `iv` | Algorithm ID  Secret key  Ciphertext  IV (default: NULL) |
| Returns    | `buf`                       | Plaintext (false on error)                               |

```
buf cbcd(flag, key, data, iv)  
```

------

## 4. Asymmetric Cryptography

##### 4.1: Generate Key Pair

| Interface  | `pk_get`      | Generates key pair                                           |
| ---------- | ------------- | ------------------------------------------------------------ |
| Parameters | `key`  `flag` | Output format (""=PEM, "bin"=raw)  Algorithm ("sm2","rsa:1024","rsa:2048") |
| Returns    | `ctx`         | Key context (false on error)                                 |

```
ctx pk_get(key, flag)  
```

##### 4.2: Import Keys

| Interface | `pk_inkey` | Imports keys from PEM/CER           |
| --------- | ---------- | ----------------------------------- |
| Parameter | `key`      | PEM/CER formatted key               |
| Returns   | `ctx`      | Key context (error code on failure) |

```
ctx pk_inkey(key)  
```

##### 4.3: Release Key Context

| Interface | `pk_free` | Releases key resources |
| --------- | --------- | ---------------------- |
| Parameter | `ctx`     | Key context            |
| Returns   | `bool`    | Success status         |

```
bool pk_free(ctx)  
```

##### 4.4: Export Public Key

| Interface | `pk_outpub` | Exports public key                   |
| --------- | ----------- | ------------------------------------ |
| Parameter | `ctx`       | Key context                          |
| Returns   | `buf`       | ASN.1 formatted key (false on error) |

```
buf pk_outpub(ctx)  
```

##### 4.5: Export Private Key

| Interface | `pk_outpri` | Exports private key                        |
| --------- | ----------- | ------------------------------------------ |
| Parameter | `ctx`       | Key context                                |
| Returns   | `buf`       | ASN.1 formatted key (false if unavailable) |

```
buf pk_outpri(ctx)  
```

##### 4.6: Public Key Encryption

| Interface  | `pk_enc`                 | Encrypts with public key                      |
| ---------- | ------------------------ | --------------------------------------------- |
| Parameters | `key`  `data`  `padding` | Key context  Plaintext  Padding ("v15","v21") |
| Returns    | `buf`                    | Ciphertext (error code on failure)            |

```
buf pk_enc(key, data, padding)  
```

##### 4.7: Private Key Decryption

| Interface  | `pk_dec`                 | Decrypts with private key         |
| ---------- | ------------------------ | --------------------------------- |
| Parameters | `key`  `data`  `padding` | Key context  Ciphertext  Padding  |
| Returns    | `buf`                    | Plaintext (error code on failure) |

```
buf pk_dec(key, data, padding)  
```

##### 4.8: Private Key Signing

| Interface  | `pk_sign`               | Creates digital signature                                 |
| ---------- | ----------------------- | --------------------------------------------------------- |
| Parameters | `key`  `data`  `scheme` | Key context  Data to sign  Scheme ("sha1v15","sha256v21") |
| Returns    | `buf`                   | Signature (error code on failure)                         |

```
buf pk_sign(key, data, scheme)  
```

##### 4.9: Public Key Verification

| Interface  | `pk_verify`                     | Verifies digital signature                    |
| ---------- | ------------------------------- | --------------------------------------------- |
| Parameters | `key`  `data`  `sign`  `scheme` | Key context  Original data  Signature  Scheme |
| Returns    | `bool`                          | Verification result                           |

```
bool pk_verify(key, data, sign, scheme)  
```

##### 4.10: RSA Public Key Operation

| Interface  | `pk_rsapub`   | Raw RSA public operation       |
| ---------- | ------------- | ------------------------------ |
| Parameters | `key`  `data` | Key context  Input data        |
| Returns    | `buf`         | Result (false on length error) |

```
buf pk_rsapub(key, data)  
```

##### 4.11: RSA Private Key Operation

| Interface  | `pk_rsapri`   | Raw RSA private operation      |
| ---------- | ------------- | ------------------------------ |
| Parameters | `key`  `data` | Key context  Input data        |
| Returns    | `buf`         | Result (false on length error) |

```
buf pk_rsapri(key, data)  
```

------

## 5. Certificates

##### 5.1: Generate CSR

| Interface  | `gp10`                       | Creates PKCS#10 certificate request                       |
| ---------- | ---------------------------- | --------------------------------------------------------- |
| Parameters | `key`  `subname`  `strength` | Key context  Subject DN  Hash strength (optional for SM2) |
| Returns    | `str`                        | PEM-formatted CSR (false on error)                        |

```
str gp10(key, subname, strength)  
```

##### 5.2: Certificate Verification

| Interface  | `x509v`          | Verifies certificate chain      |
| ---------- | ---------------- | ------------------------------- |
| Parameters | `cer`  `cerlast` | Certificate  Issuer certificate |
| Returns    | `bool`           | Verification result             |

```
bool x509v(cer, cerlast)  
```

##### 5.3: Issue Certificate

| Interface  | `x509cw`                              | Issues X.509 certificate                                     |
| ---------- | ------------------------------------- | ------------------------------------------------------------ |
| Parameters | `sn`  `md`  `p10`  `isskey`  `rootca` | Serial number  Algorithm ID  CSR  Issuer private key  Root CA |
| Returns    | `str`                                 | PEM certificate (false on error)                             |

```
str x509cw(sn, md, p10, isskey, rootca)  
```

**Implementation Guide**:
 [Natural Language Understanding NLU - Third-party Integration](https://gitee.com/kebo521/nlu3)

