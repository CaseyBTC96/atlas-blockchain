#include "blockchain.h"

#define BDL block->data.len

int tx_id_cpy(llist_node_t tx, unsigned int iter, void *buffer);

/**
 * block_hash - hashes a block using sha256
 * @block: block to hash
 * @hash_buf: buffer to store computed hash
 * Return: hash buffer or NULL
 */
uint8_t *block_hash(block_t const *block,
					uint8_t hash_buf[SHA256_DIGEST_LENGTH])
{
	size_t num_tx = 0, buff_len = 0, block_sz = 0;
	uint8_t *buffer;

	if (!block || !hash_buf)
		return (NULL);

	if (block->transactions)
		num_tx = llist_size(block->transactions);

	buff_len = sizeof(block->info) + BDL + (num_tx * SHA256_DIGEST_LENGTH);
	block_sz = sizeof(block->info) + BDL;
	buffer = calloc(1, buff_len);

	memcpy(buffer, block, block_sz);
	llist_for_each(block->transactions, tx_id_cpy, buffer + block_sz);
	SHA256(buffer, buff_len, hash_buf);

	return (hash_buf);
}
