/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 16:16:13 by                   #+#    #+#             */
/*   Updated: 2022/02/04 14:12:41 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "get_next_line_bonus.h"

char	*generate_line_candidate(int fd, int *max_len,
			t_list_sav **sav, int *is_done);
char	*split_candidate_into_result_and_rest(int fd, int max_len,
			char **candidate, t_list_sav **sav);

char	*from_read_and_restored_rest(int fd, int *max_len, int *is_done,
			char *rest_of_last_call);

char	*free_unnecessary_elements(char *result,
			t_list_sav **sav, int fd, int is_done);

char	*get_next_line(int fd)
{
	char				*result;
	int					max_len;
	int					pos_of_nl;
	static t_list_sav	*sav;
	int					is_done;

	pos_of_nl = -1;
	result = NULL;
	is_done = 0;
	if (fd < 0 || BUFFER_SIZE < 0)
		return (free_unnecessary_elements(result, &sav, fd, 0));
	while (pos_of_nl == -1 && !is_done)
	{
		free(result);
		result = generate_line_candidate(fd, &max_len, &sav, &is_done);
		if (! is_done && result)
		{
			pos_of_nl = calc_pos_of_char_n(result, '\n', max_len);
			result = split_candidate_into_result_and_rest(fd, max_len, &result,
					&sav);
		}
		else if (! free_unnecessary_elements(result, &sav, fd, is_done))
			return (NULL);
	}
	return (result);
}

char	*generate_line_candidate(int fd, int *max_len,
			t_list_sav **sav, int *is_done)
{
	int		pos_of_nl;
	char	*rest_of_last_call;
	char	*result;

	rest_of_last_call = pop_fd_res(sav, fd);
	pos_of_nl = calc_pos_of_char_n(rest_of_last_call, '\n', -1);
	if (pos_of_nl == HAS_NOT_BEEN_FOUND)
		return (from_read_and_restored_rest(fd, max_len,
				is_done, rest_of_last_call));
	(*max_len) = calc_pos_of_char_n(rest_of_last_call, 0, -1);
	result = concat_n_char_new_mem(rest_of_last_call, "", *max_len);
	free(rest_of_last_call);
	return (result);
}

char	*split_candidate_into_result_and_rest(int fd, int max_len,
			char **candidate, t_list_sav **sav)
{
	int		len_of_result;
	int		len_of_candidate;
	char	*result;
	char	*rest_of_last_call;
	char	*tmp;

	tmp = *candidate;
	result = *candidate;
	if (! result)
		return (NULL);
	len_of_result = calc_pos_of_char_n(result, '\n', max_len);
	len_of_candidate = max_len - len_of_result - SPACE_FOR_NEWLINE;
	if (max_len - SPACE_FOR_NEWLINE > len_of_result)
	{
		rest_of_last_call = concat_n_char_new_mem(&result[len_of_result
				+ SPACE_FOR_NEWLINE], "", len_of_candidate);
		save_fd_rest(sav, fd, rest_of_last_call);
	}
	result = concat_n_char_new_mem(*candidate, "",
			len_of_result + SPACE_FOR_NEWLINE);
	free(tmp);
	return (result);
}

char	*free_unnecessary_elements(char *result,
			t_list_sav **sav, int fd, int is_done)
{
	if (! result && !is_done)
		free_linked_list(sav);
	if (is_done)
		free(pop_fd_res(sav, fd));
	if (calc_pos_of_char_n(result, 0, 1) != HAS_NOT_BEEN_FOUND)
	{
		free(result);
		return (NULL);
	}
	return (result);
}

char	*from_read_and_restored_rest(int fd, int *max_len, int *is_done,
			char *rest_of_last_call)
{
	char	*buf;
	int		pos_of_nl;
	char	*result;
	int		bytes_read;

	buf = malloc(sizeof(char) * BUFFER_SIZE);
	if (! buf)
		return (NULL);
	bytes_read = read(fd, buf, BUFFER_SIZE);
	*max_len = bytes_read;
	if ((bytes_read < 0))
	{
		*is_done = 1;
		free(buf);
		return (NULL);
	}
	if (rest_of_last_call)
		*max_len = bytes_read
			+ calc_pos_of_char_n(rest_of_last_call, 0, -1);
	result = concat_n_char_new_mem(rest_of_last_call, buf, *max_len);
	pos_of_nl = calc_pos_of_char_n(result, '\n', -1);
	*is_done = ((bytes_read < BUFFER_SIZE) && (pos_of_nl == -1));
	free(rest_of_last_call);
	free(buf);
	return (result);
}
