#include "blockchain.h"

int write_blocks(llist_node_t list, unsigned int index, void *arg);

/**
 * blockchain_serialize - serializes a blockchain to file
 * @blockchain: chain to serialize
 * @path: file path to serialize to
 * Return: 1 on succerss, 0 on fail
 */
int blockchain_serialize(blockchain_t const *blockchain, char const *path)
{
	FILE *fptr = NULL;
	int blocknums = 0;
	char header[12] = {FHEADER};

	if (!blockchain || !path)
		return (0);
	blocknums = llist_size(blockchain->chain);
	memcpy(&header[7], END, 1);
	memcpy(&header[8], &blocknums, 4);
	fptr = fopen(path, "w");
	fwrite(header, 1, 12, fptr);
	llist_for_each(blockchain->chain, write_blocks, fptr);
	fclose(fptr);
	return (1);
}

/**
 * write_blocks - function to write blocks to file
 * @list: node to perform function on
 * @index: unused
 * @arg: filestream pointer
 * Return: 0
 */
int write_blocks(llist_node_t list, unsigned int index, void *arg)
{
	block_t *tmp = NULL;
	char block_buf[1116];
	uint32_t len = 0;

	(void)index;

	tmp = (block_t *)list;
	if (!strcmp(END, "\x02"))
		SWAPENDIAN(list);

	len = tmp->data.len;

	memcpy(&block_buf[0], tmp, sizeof(block_info_t));
	memcpy(&block_buf[56], &tmp->data.len, 4);
	memcpy(&block_buf[60], tmp->data.buffer, len);
	memcpy(&block_buf[60 + len], tmp->hash, 32);
	fwrite(block_buf, 1, 92 + len, arg);
	return (0);
}
