#include "hblk_crypto.h"

/**
 * sha256 - Algorithm for generating an sha256 hash of a set of bytes
 * @s: bytes to hash
 * @len: num of bytes in s
 * @digest: array to store hash
 * Return: Pointer to digest hash, or NULL
 */
uint8_t *sha256(int8_t const *s, size_t len,
				uint8_t digest[SHA256_DIGEST_LENGTH])
{
	SHA256_CTX context;

	if (!SHA256_Init(&context))
		return (NULL);
	if (!SHA256_Update(&context, s, len))
		return (NULL);
	if (!SHA256_Final(digest, &context))
		return (NULL);
	return (!digest ? NULL : digest);
}
