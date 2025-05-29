#include "hblk_crypto.h"

/**
 * ec_load - Loads a key from a file
 * @folder: Folder to load from
 * Return: Pointer to EC_KEY or NULL
 */
EC_KEY *ec_load(char const *folder)
{
	struct stat inf;
	char pub_path[1024] = {0}, priv_path[1024] = {0};
	FILE *fptr;
	EC_KEY *key = NULL;

	if (!folder)
		return (NULL);
	if (stat(folder, &inf) || (!stat(folder, &inf) && !S_ISDIR(inf.st_mode)))
		return (NULL);

	key = EC_KEY_new_by_curve_name(EC_CURVE);
	if (!key)
		return (NULL);

	memcpy(pub_path, folder, strlen(folder));
	memcpy(&pub_path[strlen(folder)], "/key_pub.pem", 12);
	memcpy(priv_path, folder, strlen(folder));
	memcpy(&priv_path[strlen(folder)], "/key.pem", 8);

	fptr = fopen(pub_path, "r");
	if (!fptr)
		return (NULL);
	PEM_read_EC_PUBKEY(fptr, &key, NULL, NULL), fclose(fptr);

	fptr = fopen(priv_path, "r");
	if (!fptr)
		return (NULL);
	PEM_read_ECPrivateKey(fptr, &key, NULL, NULL), fclose(fptr);

	return (key);
}
