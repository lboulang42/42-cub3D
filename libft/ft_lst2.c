/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 16:18:35 by lboulang          #+#    #+#             */
/*   Updated: 2023/04/22 18:37:03 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Free Lst Using Del Function Then Using free(). */
void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!del)
		return ;
	if (lst && lst->content != NULL)
	{
		del(lst->content);
		free(lst);
		lst = NULL;
	}
}

/*Delete Every Elements Of Lst Using Del Then free() */
void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;

	if (!lst)
		return ;
	if (lst)
	{
		while (*lst)
		{
			tmp = (*lst)->next;
			ft_lstdelone(*lst, del);
			*lst = tmp;
		}
	}
}

/*Use the function f on the content of every elements of lst*/
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!f)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst -> next;
	}
}

/*For Each Contents of Each Elem Of Lst, Apply f().
Create and Return New List Resulting of the application of f().
Del Is Used To Destroy The Content Of An Elem If Necessary.*/
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*result;
	t_list	*tmp;

	if (!lst)
		return (NULL);
	result = ft_lstnew(f(lst ->content));
	if (!result)
	{
		ft_lstdelone(result, del);
		return (NULL);
	}
	lst = lst -> next;
	while (lst)
	{
		tmp = ft_lstnew(f(lst->content));
		if (!tmp)
		{
			ft_lstclear(&result, del);
			return (NULL);
		}
		ft_lstadd_back(&result, tmp);
		lst = lst->next;
	}
	return (result);
}
