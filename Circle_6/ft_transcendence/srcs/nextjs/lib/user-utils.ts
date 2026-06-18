export function getAvatarUrl(user: { id?: string | null; fileId?: string | null; image?: string | null; username?: string | null; firstName?: string | null; lastName?: string | null } | null | undefined) {
	if (!user) {
		return `https://ui-avatars.com/api/?name=U&background=4f46e5&color=fff&size=128`;
	}
	if (user.fileId && user.id) {
		return `/api/user/image/${user.id}?v=${user.fileId}`;
	}
	if (user.image && !user.image.startsWith("/api/user/image/")) {
		return user.image;
	}
	const name = `${user.firstName || ""} ${user.lastName || ""}`.trim() || user.username || "U";
	return `https://ui-avatars.com/api/?name=${encodeURIComponent(name)}&background=4f46e5&color=fff&size=128`;
}
