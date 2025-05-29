#include "hblk_crypto.h"

/**
 * ec_save - saves a ec_key pair to a folder
 * @key: key to save
 * @folder: folder to save key in
 * Return: 1 on success or 0 on fail
 */
int ec_save(EC_KEY *key, char const *folder)
{
	struct stat info;
	char pub_path[1024] = {0}, priv_path[1024] = {0};
	FILE *fptr;

	if (!key || !folder)
		return (0);
	if (stat(folder, &info) || !S_ISDIR(info.st_mode))
		mkdir(folder, 0755);
	memcpy(pub_path, folder, strlen(folder));
	memcpy(&pub_path[strlen(folder)], "/key_pub.pem", 12);
	memcpy(priv_path, folder, strlen(folder));
	memcpy(&priv_path[strlen(folder)], "/key.pem", 8);
	fptr = fopen(pub_path, "w+");
	PEM_write_EC_PUBKEY(fptr, key), fclose(fptr);
	fptr = fopen(priv_path, "w+");
	PEM_write_ECPrivateKey(fptr, key, NULL, NULL, 0, NULL, NULL), fclose(fptr);
	return (1);
}
