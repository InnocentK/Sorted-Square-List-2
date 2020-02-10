
    // Special case where last item in the first INode is being deleted      
    //   and repopulation is not possible under consolidate                   
    if( (curr_len == POS) && (index_size == 1) && (POS == 0) ){
      // First the data is removed
      removed_data = it->m_dNode->m_data;
      delete it->m_dNode;
      it->m_dNode = NULL;
      m_total_size--;

      // Adjacent list is moved over
      // Takes the place of consolidate (to better handle this special case)
      it->m_dNode = ++it->m_dNode;
      --it->m_size = ++it->m_size;
      it->m_dNode = NULL;
      m_iList.erase(it);

      return removed_data;                                                    
