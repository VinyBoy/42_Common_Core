"use client"

import { useState } from "react"

type Conversation = {
    id: number
    name: string
}

const fakeUsers: Conversation[] = [
    { id: 1, name: "ArianeArt" },
    { id: 2, name: "PixelPoet" },
    { id: 3, name: "CodeMaster" },
]

const avatarColors = [
    "bg-accent-500",
    "bg-brand-500",
    "bg-success-500",
    "bg-accent-700",
    "bg-surface-500",
]

function getInitials(name: string) {
    return name.slice(0, 2).toUpperCase()
}

function getColor(id: number) {
    return avatarColors[id % avatarColors.length]
}

export default function ChatLayout() {
    const [activeConv, setActiveConv] = useState<number>(1)
    const [input, setInput] = useState("")

    const [messagesByConv, setMessagesByConv] = useState<
        Record<number, { id: number; user: string; text: string }[]>
    >({
        1: [{ id: 1, user: "ArianeArt", text: "Salut !" }],
        2: [{ id: 2, user: "PixelPoet", text: "Hello 🎨" }],
        3: [],
    })

    const currentMessages = messagesByConv[activeConv] || []

    function sendMessage() {
        if (!input.trim()) return

        setMessagesByConv(prev => ({
            ...prev,
            [activeConv]: [
                ...(prev[activeConv] || []),
                { id: Date.now(), user: "Moi", text: input },
            ],
        }))

        setInput("")
    }

    return (
        <div className="flex w-full h-full">

            <aside className="w-64 border-r bg-white">
                <h2 className="font-bold p-4 border-b">Conversations</h2>
                <ul>
                    {fakeUsers.map(conv => (
                        <li
                            key={conv.id}
                            onClick={() => setActiveConv(conv.id)}
                            className={`flex items-center gap-3 px-4 py-3 cursor-pointer transition-colors ${activeConv === conv.id
                                    ? "bg-accent-50 border-l-4 border-accent-500 font-semibold"
                                    : "hover:bg-surface-50"
                                }`}
                        >
                            <div className={`w-9 h-9 rounded-full ${getColor(conv.id)} flex items-center justify-center text-white text-xs font-bold shrink-0`}>
                                {getInitials(conv.name)}
                            </div>
                            {conv.name}
                        </li>
                    ))}
                </ul>
            </aside>

            <div className="flex flex-col flex-1 p-6">

                <div className="pb-3 border-b mb-4 flex items-center gap-3">
                    <div className={`w-10 h-10 rounded-full ${getColor(activeConv)} flex items-center justify-center text-white text-sm font-bold`}>
                        {getInitials(fakeUsers.find(u => u.id === activeConv)?.name || "")}
                    </div>
                    <h3 className="font-semibold text-lg">
                        {fakeUsers.find(u => u.id === activeConv)?.name}
                    </h3>
                </div>

                <div className="flex-1 overflow-y-auto space-y-3">
                    {currentMessages.map(m => {
                        const user = fakeUsers.find(u => u.name === m.user)
                        return (
                            <div key={m.id} className="flex items-start gap-3">
                                <div className={`w-8 h-8 rounded-full ${user ? getColor(user.id) : "bg-surface-400"} flex items-center justify-center text-white text-xs font-bold shrink-0 mt-1`}>
                                    {getInitials(m.user)}
                                </div>
                                <div className="bg-white p-3 rounded-xl shadow-sm">
                                    <p className="text-sm font-semibold">{m.user}</p>
                                    <p>{m.text}</p>
                                </div>
                            </div>
                        )
                    })}
                </div>

                <div className="mt-4 flex gap-2">
                    <input
                        className="flex-1 border rounded-lg p-2"
                        placeholder="Écrire un message..."
                        value={input}
                        onChange={e => setInput(e.target.value)}
                        onKeyDown={e => e.key === "Enter" && sendMessage()}
                    />

                    <button
                        onClick={sendMessage}
                        className="bg-black text-white px-4 py-2 rounded-lg"
                    >
                        Envoyer
                    </button>
                </div>

            </div>
        </div>
    )
}