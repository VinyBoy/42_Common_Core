"use client";
import { Dispatch, SetStateAction } from "react";

type TagSelectorProps = {
  tags: string[];
  selectedTags: string[];
  setSelectedTags: Dispatch<SetStateAction<string[]>> | ((tags: string[]) => void);
};

export default function TagSelector({ tags, selectedTags, setSelectedTags }: TagSelectorProps) {

  const toggleTag = (tag: string) => {
    if (selectedTags.includes(tag)) {
      setSelectedTags(selectedTags.filter(t => t !== tag));
    } else {
      setSelectedTags([...selectedTags, tag]);
    }
  };

  return (
    <div className="p-2 space-y-2" onClick={(e) => e.stopPropagation()} >

      <div className="flex flex-wrap gap-1">
        {selectedTags.map(tag => (
          <span
            key={tag}
            className="px-2 py-1 text-xs bg-brand-700 rounded-full"
          >
            {tag}
          </span>
        ))}
      </div>

      <div className="flex flex-wrap gap-1 max-h-32 overflow-y-auto">
        {tags.map(tag => (
          <button
            key={tag}
            onClick={() => toggleTag(tag)}
            className={`px-2 py-1 text-xs rounded-full border ${
              selectedTags.includes(tag)
                ? "bg-brand-700 text-white"
                : "bg-white/10 text-white"
            }`}
          >
            {tag}
          </button>
        ))}
      </div>
    </div>
  );
}
