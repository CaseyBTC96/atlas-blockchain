#include "blockchain.h"

/**
 * blockchain_deserialize - Loads a blockchain from file
 * @path: file to read from
 * Return: Pointer to chain or NULL
 */
blockchain_t *blockchain_deserialize(char const *path)
{
	FILE *fptr = NULL;
	char header_buf[7] = {0};
	uint8_t end;
	uint32_t numblocks, i = 0;
	blockchain_t *blockchain = calloc(1, sizeof(blockchain_t));
	block_t *block = NULL;

	if (!path)
		return (NULL);
	fptr = fopen(path, "r");
	if (!fptr)
		return (NULL);
	fread(header_buf, 1, 7, fptr);
	if (memcmp(header_buf, FHEADER, 7))
		return (NULL);
	fread(&end, 1, 1, fptr);
	fread(&numblocks, 4, 1, fptr);
	blockchain->chain = llist_create(MT_SUPPORT_FALSE);

	for (; i < numblocks; i++)
	{
		block = calloc(1, sizeof(block_t));
		fread(&block->info, 1, sizeof(block_info_t), fptr);
		fread(&(block->data.len), sizeof(uint8_t), 4, fptr);
		fread(&block->data.buffer, sizeof(uint8_t), block->data.len, fptr);
		fread(&block->hash, sizeof(uint8_t), SHA256_DIGEST_LENGTH, fptr);
		llist_add_node(blockchain->chain, block, ADD_NODE_REAR);
	}
	fclose(fptr);
	return (blockchain);
}
